@echo off
cls
echo Rpe is Executing
if "%1" == "" goto  message
echo Output is on %1
client2.exe >> %1
goto end
:message
echo Enter the Directory Where you want
echo your Output To be
echo Press Any Key
pause
:end
