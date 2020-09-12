echo off
:loop
gun.exe
std.exe
string.exe
fc string.out string.ans
if %errorlevel%==0 goto loop
pause