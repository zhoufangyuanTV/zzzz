@echo off
copy ex_queue7.in queue.in
queue.exe
fc ex_queue7.ans queue.out