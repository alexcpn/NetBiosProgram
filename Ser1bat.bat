@echo off
cls
echo Server is Executing
if "%1" == "" goto  message
echo Output is on %1
server1.exe
merbat
goto end
:message
echo Enter the Directory Where you want
echo your Output To be
echo Press Any Key
pause
:end
