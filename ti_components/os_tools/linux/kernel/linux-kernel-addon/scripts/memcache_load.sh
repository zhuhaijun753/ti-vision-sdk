
memcache_unload.sh 2>/dev/null

insmod ./bin/memcache.ko

if [ ! -f /dev/memcache ]
then
    major=$(awk '$2=="/dev/memcache" {print $1}' /proc/devices)
    mknod /dev/memcache c ${major} 0
fi

