@echo off

set sfmlVersion=3.0.2
set buildAll=1

if exist "%cd%/build" set buildAll=0
if exist "%cd%/SFML.zip" goto ExitProgram


:SetupProject
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0InstallSFML.ps1" -Command %buildAll% "%sfmlVersion%"
echo Project Setup completed...
pause
exit

:ExitProgram
echo Project is already installed...
pause
exit
