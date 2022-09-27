@echo off
mkdir Build
cmake.exe clean Build
set /P OPT=<cmake_option.txt
cmake.exe -S %~dp0 %OPT% -B Build
pause