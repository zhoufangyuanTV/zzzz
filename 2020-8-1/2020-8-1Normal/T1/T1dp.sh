while true;do
./T1make
time ./T1<T1.in>T1.out
time ./T1std<T1.in>T1.ans
if diff T1.out T1.ans -Z;then
printf AC
else
echo WA
exit 0
fi
done