#!/bin/sh
set -e
fbe="$(cd "$(dirname "$0")/.."; pwd)"
ide="$(dirname "$fbe")"

[ -d "$1/Type Library" -a -d "$2" ] || { echo "Usage: $0 <4diac project dir> <code destination dir>" >&2; exit 1; }

project="$(cd "$1"; pwd)"
projectname="$(grep '<name>' "$project/.project" | head -n 1 | sed -e 's/<\/name>$//;s/ *<name>//')"
destination="$(cd "$2"; pwd)"
workspace="$project/../${project##*/}.export"

rm -rf "$workspace"
mkdir "$workspace"

"$ide"/4diac-ide -data "$workspace" --launcher.suppressErrors -nosplash -application org.eclipse.ant.core.antRunner main -f "$fbe/scripts/export.ant" -Dproject="$project" -Ddestination="$destination" -Dprojectname="$projectname"

rm -rf "$workspace"
