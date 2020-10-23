@echo off
:loop
generator.exe>in
solution.exe<in>out
std.exe<in>ans
fc out ans
if %errorlevel%==0 goto loop
pause