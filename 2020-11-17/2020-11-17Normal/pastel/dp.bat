@echo off
:loop
data.exe
pastel.exe
std.exe
fc pastel.out pastel.ans
if %errorlevel%==0 goto loop
pause