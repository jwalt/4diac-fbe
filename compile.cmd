#!/bin/sh
echo \" <<'__________________________' >/dev/null ">NUL "
@echo off
rem CMD.EXE Batch File
cls

setlocal
set FBE=%~dp0
compile.cmd
%FBE%\scripts\run-in-shell.cmd %FBE%\scripts\compile.sh %*
exit /b
__________________________
# Shell Script
exec /bin/sh "$rootdir/scripts/compile.sh" "$@"
