#! /bin/sh
#######################################################################
######## # Copyright (C) 2011 Texas Instruments Incorporated - 
# http://www.ti.com/ # # This program is free software; you can 
# redistribute it and/or # modify it under the terms of the GNU General 
# Public License as # published by the Free Software Foundation version 
# 2.
#
# This program is distributed "as is" WITHOUT ANY WARRANTY of any 
# kind, whether express or implied; without even the implied warranty 
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
# General Public License for more details.
##############################################################################

# @desc Function to get supported dmtimers based on device tree on platform  
# @params none # @returns array of dmtimers supported source "common.sh"  
# Import do_cmd(), die() and other functions

############################# Functions #######################################
usage()
{
        echo "get_dmtimer_list.sh"
        echo "Returns dmtimers supported to be available for request"
        exit 1
}

############################ USER-DEFINED Params ############################### 



dmtimer_num=`cat /proc/device-tree/ocp/timer*/ti,hwmods`
i=0
for dir in `ls /proc/device-tree/ocp/timer*/ti,hwmods`; do
        timer_string=`cat "$dir"`
	read num1 <<<${timer_string//[^0-9]/ }
        timer_array[i]=$num1
	i=$i+1
done
echo "${timer_array[@]}"
