while true;do
./data>in
./CF575A<in>out
./CF575Aforce<in>ans
if diff out ans -Z;then
printf AC
else
echo WA
exit 0
fi
done