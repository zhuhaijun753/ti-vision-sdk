#!/bin/bash

function cleanup()
{
    # Delete the qdisc we setup earlier
    tc qdisc del dev eth0 root
}

function abort()
{
    cleanup
    exit 1
}

function usage()
{
    echo `basename $0`: " <input_file.jpg>"
    exit 1;
}

if [ $# -lt 4 ]; then
    usage
fi

INPUT_FILE="$1 $2 $3 $4"
shift 4

DEVNAME=eth0
AVBRATE=280mbit

TCPRATE=5mbit
TCPECHOPORT=7
IP=192.168.1.200

trap abort SIGINT

# Add HTB QDISC with a handle of 1: fowarding unclassified traffic to class 1:1
tc qdisc add dev $DEVNAME root handle 1: htb default 1
# Add class with handle 1:1 to the HTB QDISC 1:, limiting it's rate to $AVBRATE - this will be used to limit the AVB traffic rate
tc class add dev $DEVNAME parent 1: classid 1:1 htb rate $AVBRATE prio 100
# Add class to limit TCP traffic
tc class add dev $DEVNAME parent 1: classid 1:2 htb rate $TCPRATE

# Add a filter that classifies ip packets directed to $TCPECHOPORT to be tagged as class 1:2
tc filter add dev $DEVNAME protocol ip parent 1: prio 1 u32 match ip dport $TCPECHOPORT 0xffff flowid 1:2

# Now run the AVB talker
# Spoof the source mac address to match the DRA7xx evm demo app expected MAC address
# The --loop option repeats playback of the MJPEG input files
./avbtp_talker --dev $DEVNAME --mac-src 00:01:02:03:04:05 --tcp-send --ip $IP --tcp-port $TCPECHOPORT --input $INPUT_FILE --loop $@

cleanup
