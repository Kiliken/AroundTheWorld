@echo off

:FileCheck
if exist "%cd%/dep" goto ExitProgram
if not exist "%localappdata%/w64devkit" goto InstallGcc
if not exist "%localappdata%/w64cmake" goto InstallCMake


:SetupProject
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0InstallOpenGL.ps1"
echo Project Setup completed...
pause
exit

:InstallGcc
echo Installing Gcc...
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0InstallGcc.ps1"
echo Waiting for Gcc to finish installing...
pause
goto FileCheck

:InstallCMake
echo Installing Gcc...
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0InstallCMake.ps1"
echo Waiting for CMake to finish installing...
pause
goto FileCheck

:ExitProgram
echo Project is already installed...
pause
exit
