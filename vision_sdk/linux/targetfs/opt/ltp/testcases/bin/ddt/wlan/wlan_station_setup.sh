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

# @desc Starts a wlan station interface by invoking sta_start.sh and other
#	supporting scripts from /usr/share/wl18xx location.
#       SSID is set as environment variable WILINK_WLAN_OPEN_SSID manually for      
#       standalone LTP-DDT operation or exported from bench file when          
#       using vatf test execution. 

# @params none

# @returns 0 if commands are successful

###############################################################################

source "common.sh"  # Import do_cmd(), die() and other functions
`check_env_var 'WILINK_WLAN_OPEN_SSID'`
demo_folder=`find / -name sta_start.sh`
[ -n "$demo_folder" ] || die "Unable to find sta_start.sh in filesystem. Make sure all station scripts are present." 
demo_folder=${demo_folder%"/sta_start.sh"}
nohup "$demo_folder"/sta_start.sh &
sleep 5
scan_result=`wpa_cli scan`
sleep 5
scan_result=`wpa_cli scan_r|grep $WILINK_WLAN_OPEN_SSID`
[ -n "$scan_result" ] || die "Expected SSID $WILINK_WLAN_OPEN_SSID cannot be scanned. Check wireless router is turned on and/or check bench file"
		
# cd into demo folder since the sta_connect-ex-dhcp.sh depends on a local script
cd "$demo_folder"
connect_result=`./sta_connect-ex-dhcp.sh $WILINK_WLAN_OPEN_SSID`
[ -n "$connect_result" ] || die "Unable to connect to SSID. Check connecting manually to SSID $WILINK_WLAN_OPEN_SSID"
