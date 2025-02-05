#!/bin/sh
#********************************************************************************
# Copyright (c) 2018, 2024 OFFIS e.V.
#
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
# 
# Contributors:
#    Jörg Walter - initial implementation
# *******************************************************************************/
#

################################################################################
### low-level bootstrap/helper functions
################################################################################

set -e
exe="$0"
die() { trap "" EXIT; echo "### ${exe##*/}: $*" >&2; exit 1; }
trap '[ "$?" = 0 ] || die "Exiting due to error"' EXIT

find_basedir() {
	basedir="$(cd "$(dirname "$0")"; pwd)"
	[ -d "$basedir/scripts" ] || basedir="${basedir%/scripts}"
	[ -d "$basedir/toolchains" ] || exec "$(readlink -f "$exe")" "$@"
}

find_subdirs() {
	buildroot="$PWD"
	srcdir="$buildroot/4diac-forte/"
	[ -d "$srcdir" ] || srcdir="$buildroot/forte/"
	[ -d "$srcdir" ] || srcdir="$basedir/forte/"
	builddir="$buildroot/build"

	depdir="$basedir/dependencies/recipes"
	extradepdir="$buildroot/dependencies/recipes/"
}

cleanup_execution_environment() {
	if [ "$PATH" != "$basedir/toolchains/bin" ]; then
		PATH="$basedir/toolchains/bin"
		exec "$basedir/toolchains/bin/sh" "$0" "$@"
	fi

	export LANG=C
	export LC_ALL=C
	# make python-based code generators deterministic (e.g. open62541)
	export PYTHONHASHSEED=0
	export CGET_CACHE_DIR="$basedir/toolchains/download-cache"
	export CLICOLOR_FORCE=1
}

find_basedir
find_subdirs
cleanup_execution_environment "$@"

################################################################################
### helper functions
################################################################################

replace() { # replace varname "foo" "bar"
	eval "while [ -z \"\${$1##*\"\$2\"*}\" ]; do $1=\"\${$1%%\"\$2\"*}\"\$3\"\${$1#*\"\$2\"}\"; done";
}

update_forte_build_workaround() {
    mkdir -p "$extradepdir/forte/"
    [ -f "$extradepdir/forte/build.cmake" ] || cp "$depdir/forte/build.cmake" "$extradepdir/forte/"
    echo "$srcdir/ -X build.cmake" > "$extradepdir/forte/package.txt"
}

compile_commands=
create_compile_commands_json() {
	# skip this on anything but the native "debug" build configuration
	[ "$1" = "debug" -o "$compile_commands" = "1" ] || return 0

	# if you have https://github.com/Sarcasm/compdb installed, header files will be included,
	# which improves the functionality of many tools that read compile_commands.json
	if type compdb > /dev/null 2>&1; then
		compdb -p "$prefix/forte/build" list > "$builddir/../compile_commands.json" 2>/dev/null
	else
		cp "$prefix/forte/build/compile_commands.json" "$builddir/.."
	fi
}

detect_legacy_open62541_version() {
	local version=""

	if grep -q __UA_Client_AsyncService "$srcdir"/src/com/opc_ua/opcua_client_information.cpp; then
		version=1.4
	elif grep -q paUaServerConfig.customHostname "$srcdir"/src/com/opc_ua/opcua_local_handler.cpp; then
		version=1.3
	elif grep -q UA_Client_connectUsername "$srcdir"/src/com/opc_ua/opcua_client_information.cpp; then
		version=1.1
	elif [ -d "$srcdir"/src/com/opc_ua ] || grep -q opcua_local_handler "$srcdir"/src/modules/opc_ua/CMakeLists.txt; then
		version=1.0
	elif grep -q UA_ServerConfig_new_minimal "$srcdir"/src/modules/opc_ua/opcua_handler.cpp; then
		# this is a bit fuzzy: there were gradual changes in FORTE and open62541, so it might break depending on the exact version
		version=0.3
	else
		# There is older open62541 support before March 2017, commit
		# 843ca27be7dffddb3f0c724fa4afb3d34382bc95. 4diac-fbe did not exist back
		# then and so does not have recipes for that.
		version=0.2
	fi

	[ -z "$version" ] || ln -sf "open62541@$version" "open62541" || cp -r "open62541@$version" "open62541"
}

prepare_recipe_dir() {
	local prefix="$1"
	local recipes="$prefix/etc/cget/recipes"
	mkdir -p "$recipes"

	# try to symlink, but if that fails (windows), copy instead -- and copy every time to keep recipes up to date
	if [ -d "$extradepdir" ]; then
		cd "$extradepdir"
		for i in */; do
			ln -sf "$extradepdir/$i" "$recipes/" || cp -r "$extradepdir/$i" "$recipes/"
		done
	fi
	cd "$depdir"
	for i in */; do
		[ -d "$recipes/$i" ] || ln -sf "$PWD/$i" "$recipes/" || cp -r "$i" "$recipes/"
	done

	# for all versioned recipes: select correct package version based on SPDX file 
	cd "$recipes"
	local spdx="$srcdir/dependencies.spdx"
	if [ ! -f "$spdx" ]; then
		detect_legacy_open62541_version
		return
	fi

	for i in *@*; do
		local pkgname="${i%%@*}"

		[ ! -d "$pkgname" ] || continue

		# parse SPDX
		local found="0" version=""
		while read tag value; do
			case "$found:$tag" in
				0:PackageName:)
					[ "$value" = "$pkgname" ] || continue;
					found=1;;
				1:PackageName:)
					[ "$value" != "$pkgname" ] || continue;
					found=0;;
				1:PackageVersion:)
					version="@$value";;
			esac
		done < "$spdx"

		# select matching recipe, if any
		while [ -n "$version" ]; do
			if [ -d "$pkgname$version" ]; then
				rm -rf "$pkgname"
				ln -sf "$pkgname$version" "$pkgname" || cp -r "$pkgname$version" "$pkgname"
				break
			fi
			version="${version%[@.]*}"
		done
	done
}

################################################################################
### configuration parsing
################################################################################

defs=" "
config="unknown"
set_define() {
	local name="$1" type="$2" val="$3"
	if [ -n "$val" ]; then
		eval "[ -n \"\$defs_$name\" ] || defs=\"\$defs\$name \""
		replace val '${BASEDIR}' "$basedir"
		replace val '${BUILDROOT}' "$buildroot"
		replace val '${HOME}' "$(echo ~/)"
		replace val '$CONFIG'  "$config"
		eval "defs_$name=\"\$type:\$val\""
	elif eval "[ -n \"\$defs_$name\" ]"; then
		unset defs_$name
		defs="${defs% $name *} ${defs#* $name } "
	fi
}

reset_build_if_changed() {
	local file="$1"
	if [ -f "$cachefile" -a "$file" -nt "$cachefile" ]; then
		echo "Configuration has changed, rebuilding this configuration from scratch."
		rm -rf "$builddir"
	fi
}

deps=" "
deploy=""
forte_io=""
io_process=""
load_config() {
	local var val file="$1" config="${1%.txt}" oldpwd="$PWD"
	config="${config##*/}"

	while read line || [ -n "$line" ]; do
		line="${line%
}" # this is a CR (ASCII 0x0d) character: be tolerant to windows line endings (important for WSL)
		var_type="${line%%=*}"
		val="${line#*=}"
		var="${var_type%%:*}"
		type="${var_type#*:}"
		if [ "$type" = "$var" ]; then
			type="STRING"
		fi

		case "$var" in
			//*|"#"*|"") ;;
			" "*|*" ") die "Extra spaces in config file not supported.";;

			DEPS)
				if [ "${val#-}" != "$val" ]; then
					val="${val#-}"
					deps="${deps%% $val *} ${deps#* $val }"
				else
					deps=" $val$deps"
				fi;;

			DEPLOY)
				if [ -n "$val" ]; then
					deploy="${deploy}
$val"
				else
					deploy=""
				fi;;

			include)
				cd "$(dirname "$file")"
				load_config "$val"
				cd "$oldpwd";;

			IO_PROCESS)
				[ -z "$io_process" ] || set_define "FORTE_MODULE_${io_process}" "BOOL" "OFF"
				[ -z "$val" ] || set_define "FORTE_MODULE_${val}" "BOOL" "ON"
				io_process="$val";;

			IO)
				if [ -n "$val" ]; then
					set_define "FORTE_IO" "BOOL" "ON"
					set_define "FORTE_IO_$val" "BOOL" "ON"
					forte_io="_$val"
				else
					# FIXME: once there are multiple IO modules, revise this logic
					set_define "FORTE_IO" "BOOL" "OFF"
					set_define "FORTE_IO$forte_io" "BOOL" "OFF"
					forte_io=""
				fi;;

			MODULE|COM)
				val="$val,"
				while [ "${val#*,}" != "$val" ]; do
					if [ "${val#-}" != "$val" ]; then
						val="${val#-}"
						set_define "FORTE_${var}_${val%%,*}" "BOOL" "OFF"
					else
						set_define "FORTE_${var}_${val%%,*}" "BOOL" "ON"
					fi
					val="${val#*,}"
				done;;

			*) set_define "$var" "$type" "$val";;
		esac
	done < "$file"
}

################################################################################
### build process
################################################################################

keep_going=
build_one() {
	local file="$1" config="${1%.txt}"
	config="${config##*/}"
	prefix="$builddir/$config"
	cachefile="$prefix/forte/build/CMakeCache.txt"

	reset_build_if_changed "$file"

	prepare_recipe_dir "$prefix"

	set_define ARCH STRING "native-toolchain"

	set_define "CMAKE_SKIP_RPATH" "BOOL" "ON"
	load_config "$file"

	target="${defs_ARCH#*:}"
	"$basedir/toolchains/install-crosscompiler.sh" "$target"
	"$basedir/toolchains/bin/cget" -p "$prefix" init -t "$basedir/toolchains/$target.cmake" --ccache

	set_define ARCH
	set -- -DCMAKE_INSTALL_PREFIX:STRING="$prefix/output"
	for name in $defs; do
		eval "type=\"\$defs_$name\""
		val="${type#*:}"
		type="${type%%:*}"
		#echo "$name: $val"
		set -- "$@" "-D$name:$type=$val"
	done

	"$basedir/toolchains/bin/cget" \
		-p "$prefix" install $verbose \
		$deps \
		"$@" \
		-DCMAKE_INSTALL_PREFIX:STRING="$prefix" \
		-G "$generator" \
		|| die "Dependencies of configuration '$config' failed"
	if [ -f "$prefix/forte/build/CMakeCache.txt" -a "$basedir/dependencies/recipes/forte/build.cmake" -nt "$prefix/forte/build/CMakeCache.txt" ]; then
		rm -rf "$prefix/forte"
	fi

	"$basedir/toolchains/bin/cget" \
		-p "$prefix" build -T install $verbose \
		-B "$prefix" \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		"$@" forte \
		-G "$generator" \
		|| {
			[ -z "$keep_going" ] || return 0
			die "Build of configuration '$config' failed"
		}

	"$basedir/toolchains/etc/package-dynamic.sh" "$target" "$prefix/output/bin/forte" || true
	create_compile_commands_json "$config"

	if [ -n "$deploy" ]; then
		(
			cd "$prefix"
			exec "$SHELL" -c "$deploy"
		)
	fi
}

################################################################################
### main script
################################################################################

verbose=--log
generator=Ninja
while [ -n "$1" ]; do
	case "$1" in
		-v) verbose="-v";;
		-d)
			generator="Unix Makefiles";
			export MAKEFLAGS=-j1;
			export NINJAFLAGS=-j1;
			export CMAKE_BUILD_PARALLEL_LEVEL=1;
			set_define CMAKE_VERBOSE_MAKEFILE BOOL ON;;
		-c) compile_commands=1;;
		-k) keep_going=1;;
		-h) echo "Usage: $0 [-v] [-c] [-k] [config-name ...]" >&2; exit 0;;
		-*) echo "Unknown flag: $1 -- ignoring";;
		*) break;
	esac
	shift
done

update_forte_build_workaround

if [ $# = 0 ]; then
	set -- configurations/*.txt
elif [ -d "$1" ]; then
	cd "$1"
	set -- *.txt
fi

for i in "$@"; do
	[ -f "$i" ] || i="configurations/$i.txt"
	config="$(cd "$(dirname "$i")"; echo "$PWD/$(basename "$i")")"
	( cd "$basedir"; build_one "$config"; )
done
