#!/bin/sh
echo \" <<'__________________________' >/dev/null ">NUL "
@echo off
rem CMD.EXE Batch File
cls

setlocal
set FBE=%~dp0\..

if exist %FBE%\toolchains\bin\sh.exe goto noinstall
	pushd %FBE%\toolchains
	call etc\install-Windows.cmd
	popd
:noinstall

%FBE%\toolchains\bin\sh.exe %*
exit /b
__________________________
# Shell Script
exec /bin/sh "$@"
