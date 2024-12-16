@echo off
 
::检测时间间隔，单位：秒
set _interval=60
::需要守护的进程名称
set _processName=fanctrl.exe
 
:loop
::检查进程是否运行
tasklist | find "fanctrl.exe" > nul
 
if %errorlevel% neq 0 (
    echo Start %_processName%-%time%
    start "" "%~dp0\fanctrl.exe"
)
 
::等待一段时间再次检查
timeout /t %_interval% /nobreak > nul
goto loop