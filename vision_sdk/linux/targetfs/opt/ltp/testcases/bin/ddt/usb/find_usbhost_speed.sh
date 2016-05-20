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

# Return speed for usbhost interfaces

source "common.sh"
speed=$1
case "$speed" in
	"superspeed" ) echo "5000"
	;;
	"highspeed" ) echo "480"
	;;
	"fullspeed" ) echo "12"
	;;
	"lowspeed" ) echo "1.5"
	;;
	*)
	echo "Unsupported usb speed" 
	exit 1
	;;
esac
