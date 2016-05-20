devnum=`cat /proc/devices | grep cam | cut -d ' ' -f1`
echo "cam device major num is $devnum"

NODE_NUMS="1 2 3 4 5 6 7"
for NUM in $NODE_NUMS ; do
    mknod /dev/cam$NUM c $devnum $NUM
done

for NODE in $(ls /dev/cam*); do
    sensor-cfg --dev $NODE
done
