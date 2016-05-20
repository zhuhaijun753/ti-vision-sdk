#!/bin/sh
#
# Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation version 2.
#
# This program is distributed "as is" WITHOUT ANY WARRANTY of any
# kind, whether express or implied; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# Performs dd read test from hwrng device and prints out throughput in trace
# Inputs: 
# $1 - device for hwrng, example /dev/hwrng
# $2 - block size for dd command, example 512
# $3 - number of blocks, example 1024
# Output: None

source "common.sh"
source "st_log.sh"

device_name=$1
block_size=$2
block_count=$3
do_cmd "time -p dd if=$device_name of=randomness bs=$block_size count=$block_count 2> rng_temp.log"
output=`cat rng_temp.log`
while read line                                               
do                                                            
    if [[ "${line}" == *sys* ]]; then
    time=$( echo "$line"|awk -F'sys ' '{print $2;}' )                 
    echo $time
  fi                                                 
done <<< "$output" 
bytes_transferred=$((block_size * block_count))
throughput=`echo "scale=3; $bytes_transferred/$time" | bc` 
test_print_trc "|BYTES_READ:"`printf '%.2f' $bytes_transferred`" B|"
test_print_trc "|TIME TAKEN:"`printf '%.2f' $time`" s|"
test_print_trc "|PERFDATA|READ|throughput:"`printf '%.2f' $throughput`" B/s|"
do_cmd "rm rng_temp.log"

