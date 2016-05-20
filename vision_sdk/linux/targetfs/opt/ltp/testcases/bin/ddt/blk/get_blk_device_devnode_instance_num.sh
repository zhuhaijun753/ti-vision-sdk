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

# Get mmc instance number for mmc or emmc
# Input: DEVICE_TYPE like 'mmc' or 'emmc' 
# Output: instance number 

source "blk_device_common.sh"

if [ $# -ne 1 ]; then
    echo "Error: Invalid Argument Count"
    echo "Syntax: $0 <device_type>"
    exit 1
fi

instance_num=''
signature='mmcblk*p1' # MMC signature by default
device_type=$1
############################ USER-DEFINED Params ##############################
# Try to avoid defining values here, instead see if possible
# to determine the value dynamically
case $ARCH in
esac
case $DRIVER in
esac
case $SOC in
esac
case $MACHINE in
esac

######################### Logic here ###########################################
if [ "$device_type" == 'emmc' ]; then
  signature='mmcblk*boot*'
fi
if [ -z $instance_num ]; then
  instance_num=`find /sys/devices/ -type d -name $signature | egrep "mmc[[:digit:]]+" -o | head -n 1 | egrep "[[:digit:]]+" -o` || die "Failed to get instance number for $device_type"
fi

echo $instance_num
