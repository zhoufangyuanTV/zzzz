@echo off
:loop
AGC022Dmake.exe>AGC022D.in
AGC022D.exe<AGC022D.in>AGC022D.out
AGC022Dstd.exe<AGC022D.in>AGC022D.ans
fc AGC022D.out AGC022D.ans
if %errorlevel%==0 goto loop
pause