#! /bin/sh
############################################################################### 
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
###############################################################################

# @desc Measure raw performance when using dd to write to device node
# @params d) device_type
#         b) block
#         c) count
# @returns none

source "common.sh"  # Import do_cmd(), die() and other functions

############################# Functions #######################################
usage()
{
	echo "$0 <device_type> <blocks> <count>"
	exit 1
}

# calculate throughput based on real time of dd output
# input: real_time from dd command, ex, 'real 0m 0.50s
#        bs: blocks like 1M, 512, 10M, 1G
#
# output: perf data in MB/S
calculate_perf_after_dd(){
  t=$1
  size=$2

  m=`echo $t |awk '{print $2}' |sed 's/m//' `
  s=`echo $t |awk '{print $3}' |sed 's/s//' `
  # real_time in second
  real_time=`echo "${m} * 60 + ${s}" |bc`

  perf=`echo "scale=1; ${size} / ${real_time} /1024 /1024" |bc`
  echo $perf
}


############################ Script Variables ##################################

################################ CLI Params ####################################
# Please use getopts
while getopts  :d:b:c:h arg
do case $arg in
        d)      device_type="$OPTARG";;
        b)      bs="$OPTARG";;
        c)      count="$OPTARG";;
        h)      usage;;
        :)      die "$0: Must supply an argument to -$OPTARG.";; 
        \?)     die "Invalid Option -$OPTARG ";;
esac
done

suffix=`echo "$bs" |sed 's/[0-9]*//' `
case $suffix in
  "K") unit=1024 ;;
  "M") unit=`echo 1024*1024|bc` ;;
  "G") unit=`echo 1024*1024*1024|bc` ;;
  "") unit=1 ;;
  *) die "This suffix of blocks $bs is not supported. This script only supports 'K', 'M', 'G' or no suffix" ;;  
esac

############################ USER-DEFINED Params ###############################
# Try to avoid defining values here, instead see if possible
# to determine the value dynamically. ARCH, DRIVER, SOC and MACHINE are 
# initilized and exported by runltp script based on platform option (-P)

# Define default values for variables being overriden
case $ARCH in
esac
case $DRIVER in
esac
case $SOC in
esac
case $MACHINE in
esac

########################### DYNAMICALLY-DEFINED Params #########################
test_dnode=`get_blk_device_node.sh "$device_type"` || die "Error getting test dev node:$test_dnode"

########################### REUSABLE TEST LOGIC ###############################
test_print_trc "Test starting..."

bs_num=`echo "$bs" |grep -E -o '[0-9]*'`
filesize=`echo "$bs_num * $unit * $count" |bc`
test_print_trc "filesize: $filesize"

t1=`do_cmd time dd if=/dev/zero of=$test_dnode bs=$bs count=$count 2>&1 |grep real`
echo $t1
write_perf=`calculate_perf_after_dd "$t1" "$filesize"` ||die "error getting write perf:$write_perf"
test_print_trc "|PERFDATA|bsize:${bs}|iomode:write|throughput:${write_perf}MB/S|"
t2=`do_cmd time dd if=$test_dnode of=/dev/null bs=$bs count=$count 2>&1 |grep real`
echo $t2
read_perf=`calculate_perf_after_dd "$t2" "$filesize"` ||die "error getting read perf:$read_perf"
test_print_trc "|PERFDATA|bsize:${bs}|iomode:read|throughput:${read_perf}MB/S|"



