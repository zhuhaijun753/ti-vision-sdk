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

# search for PCI SATA devices

source "common.sh"

right_dev=''

devices=`ls /sys/block |grep sd`
for device in $devices
  do
    pci_interface=`udevadm info --attribute-walk --path=/sys/block/$device|grep -m 1 -i "pci"`
    if [ -n "$pci_interface" ];
    then
      echo $device
      right_dev=$device
    fi
done
if [ -z $right_dev ];
then
  test_print_trc " ::"
  test_print_trc " :: Failed to find PCI SATA interface. Exiting PCI SATA tests..."
  test_print_trc " ::"
  exit 2	
fi
