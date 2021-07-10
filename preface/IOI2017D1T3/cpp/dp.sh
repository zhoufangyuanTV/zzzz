i=0
while true;do
((i++))
./gen>in $i
./tmp<in>out
./std<in>ans
if diff out ans -Z;then
echo AC $i
else
echo WA
exit 0
fi
done