# Chromebook-fan-controler-win
if you need to stop the fan when the Chromebook running Windows is cool, this is what you need.
# How to use
## 1.Download fanctrl.exe & daemon.bat and put them in the same fold.
## 2.Add daemon.bat to task sheduler
use system acount(or other accont to avoid seeing the console) and run daemon.bat when users login in 
## 3.Enjoy
 I don't how English version of windows show these options, so it's hard to describe the process in English, if you can't understand, translate the Chinese version, it's detailed.
### DO NOT DIRECTLY USE EXE FILE, ITS CRASH COULD CAUSE FAN STOP EVEN WHEN IT'S HOT
### Different models and different driver versions may have different formats of ectool output temperature, which will cause the programme to run abnormally, and you can modify the code and compile it by yourself.
# 如何使用
## 1.下载fanctrl.exe & daemon.bat并置于同一目录。
## 2.把daemon.bat加入计划任务程序
运行任务时使用的账户选system或者你不用的账户，触发器选登陆时，操作选启动程序-daemon.bat，条件里该去的都去掉。
## 3.完成
### 不要直接用exe，exe异常退出会导致风扇始终不转而过热
### 不同的机型和不同的驱动版本可能ectool输出温度的格式不同，造成程序运行异常，可以自行修改代码并编译
