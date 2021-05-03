@echo off
:loop
g.exe
grader.exe<g.in>g.out
fc g.out g.ans
if %errorlevel%==0 goto loop
pause