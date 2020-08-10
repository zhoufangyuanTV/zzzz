echo off
:loop
data.exe
7-29NormalT1.exe
std.exe
fc journey.out journey.ans
if %errorlevel%==0 goto loop
pause