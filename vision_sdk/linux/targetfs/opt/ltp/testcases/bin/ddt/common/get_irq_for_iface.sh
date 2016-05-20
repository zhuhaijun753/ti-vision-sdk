#! /bin/sh
############################################################################### 
# Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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

# @desc returns irq number associated with an interface
# @params i) interface 
# @history 2013-04-22: First version

source "common.sh"  # Import do_cmd(), die() and other functions

############################# Functions #######################################
usage()
{
	echo "$0 -i <interface>. Where interface=eth0, mmc0, etc."
	exit 1
}

find_irq()
{
	NAME=`cat /proc/interrupts  | grep -v gpio | grep $NAME | head -1 | cut -d':' -f 1`
}

find_irq_based_on_device_tree()
{
  index=$1 # Index of interested interrupt in case multiple interrupts per iface type
  NAME=`cat /proc/interrupts | grep -i $NAME | head -n $index | tail -n 1| cut -d':' -f 1`
}
############################ Script Variables ##################################
# Define default valus if possible

################################ CLI Params ####################################
# Please use getopts
while getopts  :i:h arg
do case $arg in
        i)      INTERFACE="$OPTARG";;
        h)      usage;;
        :)      die "$0: Must supply an argument to -$OPTARG.";; 
        \?)     die "Invalid Option -$OPTARG ";;
esac
done

############################ USER-DEFINED Params ###############################
# Try to avoid defining values here, instead see if possible
# to determine the value dynamically. ARCH, DRIVER, SOC and MACHINE are 
# initilized and exported by runltp script based on platform option (-P)

# Define default values for variables being overriden
IRQ=""
NAME="$INTERFACE"

# Map Interface name to name or irq in /proc/interrupts
case $INTERFACE in
eth*)
  find_irq_based_on_device_tree 2
	case $MACHINE in
	omap5-evm)
		NAME='109';;
	keystone-evm)
    NAME='80';;
	esac
	;;
esac

########################### DYNAMICALLY-DEFINED Params #########################
# Try to use /sys and /proc information to determine values dynamically.
# Alternatively you should check if there is an existing script to get the
# value you want
echo $NAME | grep -E '^[[:digit:]]+' > /dev/null || find_irq

########################### REUSABLE TEST LOGIC ###############################
# DO NOT HARDCODE any value. If you need to use a specific value for your setup
# use USER-DEFINED Params section above.
echo $NAME | grep -E '^[[:digit:]]+' > /dev/null || die "Could not find irq number for $NAME"
N=`echo $NAME | cut -d' ' -f 1`; echo $N
