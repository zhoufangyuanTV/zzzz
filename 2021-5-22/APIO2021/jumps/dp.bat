@echo off
:loop
generator
jumps<jumps.in>jumps.out
std
fc jumps.out jumps.ans
if %errorlevel%==0 goto loop
pause