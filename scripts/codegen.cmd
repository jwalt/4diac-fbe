@echo off
setlocal
"%~dp0\..\toolchains\bin\python.exe" "%~dp0\codegen.py" %*
if %0 == "%~0" pause
