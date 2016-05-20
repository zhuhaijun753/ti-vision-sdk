#! /bin/sh
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

# Find and remove any loaded usb gadget modules

source "common.sh"

module_output=`cat /proc/modules|grep ^"g_"`
module_array=($module_output)
echo ${module_array[0]}
if [ ! -z "${module_array[0]}" ]; then
        `modprobe -r "${module_array[0]}"`
fi
