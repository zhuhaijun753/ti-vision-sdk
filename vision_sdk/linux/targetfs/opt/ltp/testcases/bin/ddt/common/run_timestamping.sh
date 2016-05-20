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

# @desc Run timestamping https://www.kernel.org/doc/Documentation/networking/timestamping/timestamping.c

source "common.sh"  # Import do_cmd(), die() and other functions
source "st_log.sh"  # Import log functions such as test_print_trc()

############################# Functions #######################################
usage()
{
	echo "run_timestamping.sh -i <interface> [other timestamping options (see timestamping help)"
	echo " -i <interface>: Ethernet interface to run test on"
        echo " -t <duration>: Run test for <duration> secs"
	echo " all other args are passed as-is to timestamping"
	echo " timestamping help:"
        echo `timestamping`
	exit 1
}

################################ CLI Params ####################################
# Please use getopts
while getopts  :i:t:h arg
do case $arg in
        i)      INTERFACE="$OPTARG";; 
        t)      DURATION="$OPTARG"; shift 4 ;;
        h)      usage;;
        :)      ;; 
        \?)     ;;
esac
done
echo $INTERFACE
echo $DURATION
# Define default values if possible

############################ USER-DEFINED Params ###############################
# Try to avoid defining values here, instead see if possible
# to determine the value dynamically. ARCH, DRIVER, SOC and MACHINE are 
# initilized and exported by runltp script based on platform option (-P)
case $ARCH in
esac
case $DRIVER in
esac
case $SOC in
esac
case $MACHINE in
esac
# Define default values for variables being overriden

########################### DYNAMICALLY-DEFINED Params #########################
# Try to use /sys and /proc information to determine values dynamically.
# Alternatively you should check if there is an existing script to get the
# value you want

: ${INTERFACE:=eth0}
: ${DURATION:=60}

########################### REUSABLE TEST LOGIC ###############################
# DO NOT HARDCODE any value. If you need to use a specific value for your setup
# use USER-DEFINED Params section above.

[ -n "$INTERFACE" ] || die "Interface could not be determined. Please specify it when calling the script. \
(i.e. run_timestamping.sh -i <interface>)"


test_print_trc "Starting timestamping test"

do_cmd "timeout -t ${DURATION} timestamping ${INTERFACE} $*"

