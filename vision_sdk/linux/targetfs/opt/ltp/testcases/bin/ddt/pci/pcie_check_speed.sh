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

# Check PCIe running speed by LnkSta

source "common.sh"

get_rc_id()
{
  rc_id=`lspci -n |grep -E "^00:" |cut -d" " -f3`
  if [ -z $rc_id ]; then
    die "Could not get RC ID"
  fi
  echo "$rc_id"
}

get_ep_id()
{
  ep_id=`lspci -n |grep -E "^01:" |head -1 |cut -d" " -f3`
  if [ -z $ep_id ]; then
    die "Could not get EP ID"
  fi
  echo "$ep_id"
}

get_pcie_speed()
{
  pci_id=$1
  item2check=$2 # 'lnkcap:' or 'lnksta:'

  lnk_speed=`lspci -d "$pci_id" -vv |grep -i "$item2check" |grep -Eoi "Speed [0-9\.]+GT/s" |cut -d' ' -f2 |cut -d'G' -f1 `
  if [ -z $lnk_speed ]; then
    die "Could not get pcie speed capability or status"
  fi
  echo $lnk_speed
}

get_pcie_width()
{
  pci_id=$1
  item2check=$2 # 'lnkcap:' or 'lnksta:'

  lnk_width=`lspci -d "$pci_id" -vv |grep -i "$item2check" |grep -Eoi "Width x[0-9]+" |grep -Eo "[0-9]+" `
  if [ -z $lnk_width ]; then
    die "Could not get pcie width capability or status"
  fi
  echo $lnk_width
}


is_lnksta_expected()
{
  rc_cap=$1
  ep_cap=$2
  lnksta=$3
  item=$4   # speed or width

  unit=''
  if [ $item = 'speed' ]; then
    unit="GT/S"
  elif [ $item = 'width' ]; then
    unit=""
  else
    die "Wrong item passed to is_lnksta_expected function"
  fi

  if [ $(echo "$rc_cap < $ep_cap" |bc -l) -ne 0 ]; then
    expected=$rc_cap
  else
    expected=$ep_cap
  fi

  if [ -z $expected ]; then
    die "Could not find the expected lnksta"
  fi
  echo "expected lnksta:$expected"

  if [ $(echo "$lnksta == $expected" |bc -l) -eq 1 ]; then
    echo "The PCIe LnkSta is at expected ${item}: ${expected}$unit "
  elif [ $(echo "$lnksta > $expected" |bc -l) -eq 1 ]; then
    die "The PCIe LnkSta $item is greater than the $item capability. Maybe the reporting is wrong!"
  else
    die "The PCIe LnkSta ${item} is lower than the expected $item:${expected}$unit " 
  fi
}


#########################################################################
#echo "::::::::PCIe numeric IDs::::::::"
do_cmd "lspci -nn"
#echo "::::::::End of PCIe numeric IDs::::::::"

echo "=============Output of lspci -vv=============="
do_cmd 'lspci -vv'
echo "=============================================="

rc_id=`get_rc_id` || die "error getting rc_id: $rc_id"
ep_id=`get_ep_id` || die "error getting ep_id: $ep_id"
rc_speed_cap=`get_pcie_speed "$rc_id" "lnkcap:" ` || die "error when getting speed cap for RC:${rc_speed_cap}"
rc_width_cap=`get_pcie_width "$rc_id" "lnkcap:" ` || die "error when getting width cap for RC:${rc_width_cap}"
ep_speed_cap=`get_pcie_speed "$ep_id" "lnkcap:" ` || die "error when getting speed cap for EP:${rc_speed_cap}"
ep_width_cap=`get_pcie_width "$ep_id" "lnkcap:" ` || die "error when getting width cap for EP:${rc_width_cap}"

rc_speed_sta=`get_pcie_speed "$rc_id" "lnksta:" ` || die "error when getting speed sta for RC:${rc_speed_sta}"
rc_width_sta=`get_pcie_width "$rc_id" "lnksta:" ` || die "error when getting width sta for RC:${rc_width_sta}"
ep_speed_sta=`get_pcie_speed "$ep_id" "lnksta:" ` || die "error when getting speed sta for EP:${rc_speed_sta}"
ep_width_sta=`get_pcie_width "$ep_id" "lnksta:" ` || die "error when getting width sta for EP:${rc_width_sta}"

echo "::::::::RC and EP Capbility::::::::"
echo "::::::::RC Speed ${rc_speed_cap}GT/s::::::::"
echo "::::::::RC Width x${rc_width_cap}::::::::"
echo "::::::::EP Speed ${ep_speed_cap}GT/s::::::::"
echo "::::::::EP Width x${ep_width_cap}::::::::"
echo "::::::::::::::::::::::::::::::::::"

echo "::::::::RC and EP Link Status::::::::"
echo "::::::::RC Speed ${rc_speed_sta}GT/s::::::::"
echo "::::::::RC Width x${rc_width_sta}::::::::"
echo "::::::::EP Speed ${ep_speed_sta}GT/s::::::::"
echo "::::::::EP Width x${ep_width_sta}::::::::"
echo "::::::::::::::::::::::::::::::::::"

echo "=============================================="

# check if the speed and width is at expected through LnkSta 
is_lnksta_expected $rc_speed_cap $ep_speed_cap $rc_speed_sta 'speed' || die "PCIe link speed is not at expected speed!"

is_lnksta_expected $rc_width_cap $ep_width_cap $rc_width_sta 'width' || die "PCIe link width is not at expected width!"


# end of script
