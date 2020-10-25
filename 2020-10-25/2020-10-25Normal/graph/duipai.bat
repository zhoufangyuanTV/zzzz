@echo off
:loop
makedata.exe
graph.exe
spj.exe
if errorlevel 1 pause
goto loop