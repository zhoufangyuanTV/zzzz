echo off
:loop
T1gun.exe>T1.in
T1.exe<T1.in>T1.out
T1std.exe<T1.in>T1.ans
fc T1.out T1.ans
if %errorlevel%==0 goto loop
pause