echo off
:loop
T2gun.exe>T2.in
T2.exe<T2.in>T2.out
T2std.exe<T2.in>T2.ans
fc T2.out T2.ans
if %errorlevel%==0 goto loop
pause