@echo off
:loop
make
grader<sample.txt>result
sel
if %errorlevel%==0 goto loop
pause