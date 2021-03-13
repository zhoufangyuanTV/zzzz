@echo off
:loop
data>C.in
C<C.in>C.out
spj>C.ans
fc C.ans ac
if %errorlevel%==0 goto loop
pause