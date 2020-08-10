while true; do
./make>cheese.in #出数据
./cheese<cheese.in>cheese.out #被测程序
./cheesestd<cheese.in>cheese.ans #正确（暴力）程序
if diff cheese.out cheese.ans -Z; then #比较两个输出文件
printf AC #结果相同显示AC
else
echo WA #结果不同显示WA，并退出
#cat tmp.out tmp2.out
exit 0
fi #if的结束标志,与C语言相反，0为真
done