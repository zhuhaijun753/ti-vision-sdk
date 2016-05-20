#!/bin/sh
#/*
# * TI GLSDK Thermal Information Utility
# *
# * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
# * Author: Ravikumar Kattekola <rk@ti.com>
# *
# * copy of this software and associated documentation files (the "Software"),
# * to deal in the Software without restriction, including without limitation
# * the rights to use, copy, modify, merge, publish, distribute, sublicense,
# * and/or sell copies of the Software, and to permit persons to whom the
# * Software is furnished to do so, subject to the following conditions:
# *
# * The above copyright notice and this permission notice shall be included in
# * all copies or substantial portions of the Software.
# *
# * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# * IN THE SOFTWARE.
# * This program is free software; you can redistribute it and/or
# */

header="<--- Welcome to GLSDK Thermal Information utility --->"
thermaldir="/sys/devices/virtual/thermal"
basename=$thermaldir"/thermal_zone"
basecooling="/sys/devices/virtual/thermal/cooling_device"
temp="/temp"
type="/type"
cst="/cur_state"
mst="/max_state"
nrzones=5
nrcoolers=1
choice=1
display_temp()
{
	clear
	echo "$header"
	echo "-------------------------------------------------------------------"
	echo "|   Zone No    |    Type     |    Temperature(milli Celsius)      |"
	echo "-------------------------------------------------------------------"
	c=0
	while [ $c -le $(( $nrzones - 1 )) ]
	do
		echo "	$c		`cat $basename$c$type`		`cat $basename$c$temp`	"
		c=$(( $c + 1 ))
	done
	echo "-------------------------------------------------------------------"
	echo " "
}

list_cooling_devices()
{
	clear
	echo $header
	echo "-------------------------------------------------------------------"
	echo "|   Cooler No    |    Type           |    Cooling level           |"
	echo "|                |                   |    Current |  Max          |"
	echo "-------------------------------------------------------------------"
	coolers=$(ls $thermaldir | grep "cooling_device")
	nrcoolers=0
	for i in $coolers
	do
		nrcoolers=$(( $nrcoolers + 1 ))

	done

	c=0
	while [ $c -le $(( $nrcoolers - 1 )) ]
	do
		echo "	$c	   `cat $basecooling$c$type`	   `cat $basecooling$c$cst`   |    `cat $basecooling$c$mst`"
		c=$(( $c + 1 ))
	done
	echo "-------------------------------------------------------------------"
	echo " "
}

_menu()
{

	echo 'Here is what you can do next:'
	echo '
	1. See/Refresh temp details
	2. See trip point info
	3. Emulate tempearature
	4. Heat up a zone
	5. Un-do Heat up
	6. See cooling info
	7. Exit
		'
	read -p 'So, What is it gonna be:' choice
}

lets_get_hot()
{
	echo "Currently Supported Zones: 0"
	read -p 'Do you wanna heat up zone 0? [type y/n]' yn
	if [ "$yn" == "y" ];
	then
		echo "This utility needs cpuloadgen binary to heat up cpu"
		echo "make sure you got that.."
		cpuloadgen 100 100 &
		echo " "
	else
		echo "No? Good lets keep it cool.."
	fi
}

cool_down_dude()
{
	echo 'Cooling down system'
	echo 'Searching for bg cpuload generator to be killed'
	if [ "$(ps | grep [cpu]loadgen | awk '{print $1}')" != "" ];
	then
		echo $(ps | grep [cpu]loadgen | awk '{print $1}')
		kill -9 $(ps | grep [cpu]loadgen | awk '{print $1}')
	else
		echo "None Found.."
	fi
	echo 'done..'

}

fake_the_heat()
{
	read -p 'Enter the zone number:' zone
	read -p 'Enter the temperature to fake(milli Celsius):' ftemp
	basename="/sys/devices/virtual/thermal/thermal_zone"
	etemp="/emul_temp"
	if [ -e $basename$zone$etemp ];
	then
		echo $ftemp > $basename$zone$etemp
		echo 'Refresh details to see the change..'
	else
		echo "Note: Thermal Emulation entries were not found in sysfs
		Please rebuild Linux Kernel with CONFIG_THERMAL_EMULATION enabled
		Location:
			-> Device Drivers
				-> Generic Thermal sysfs driver (THERMAL [=y])
					[*]   Thermal emulation mode support"
	fi
}

list_trip_info()
{
	tmp="_temp"
	typ="_type"
	trp="/trip_point_"
	read -p 'Enter zone number:' zn
	tr=$basename$zn
	echo "Tripping point info for zone - $zn"
	echo "Trip no	Trip Type		Tripping Temp(milli Celsius)"

	trips=$(ls $tr | grep "trip_point_" | grep "_temp")
	nrtrips=0
	for i in $trips
	do
		nrtrips=$(( $nrtrips + 1 ))

	done

	echo "-------------------------------------------------------------------"
	echo "|   Trip No      |    Type           | Temperature (m celsius)    |"
	echo "|                |                   |                            |"
	echo "-------------------------------------------------------------------"
	c=0

	while [ $c -le $(( $nrtrips - 1 )) ]
	do
		echo "$c		`cat $tr$trp$c$typ`		`cat $tr$trp$c$tmp`"
		c=$(( $c + 1 ))
	done

	echo "-------------------------------------------------------------------"
}

display_main()
{
		display_temp
		_menu
	c=1
	while [ $c -ge 1 ]
	do
		display_temp

		case $choice in
		1)	display_temp
			;;
		2)	list_trip_info
			;;
		3)	fake_the_heat
			;;
		4)	lets_get_hot
			;;
		5)	cool_down_dude
			;;
		6)	list_cooling_devices
			;;
		7)	echo 'Bye Bye.. Have a good day..'
			exit 0
			;;
		*)	clear
			;;
		esac
		_menu
		c=$(( $c + 1 ))
	done
}

main()
{
	zones=$(ls $thermaldir | grep "thermal_zone")
	nrzones=0
	for i in $zones
	do
		nrzones=$(( $nrzones + 1 ))

	done
	display_main
}
main

