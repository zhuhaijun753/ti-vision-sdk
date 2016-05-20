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

# Functions related to block device partition and its size 

source "common.sh"

############################ Functions ################################

# Create three partitions on blk device like emmc, usbhost, msata/sata etc if there
#   is no partition in it. 
# And mark the first partition as boot partition so the test won't touch it in case 
#   user use it as boot partition later on;
# And also make initial filesystem on these three partitions
# 3rd partition size is whatever left on the card
# Input:
#       basenode like /dev/mmcblk0, /dev/sda etc
#       1st partition size in MB
#       2nd partition size in MB
create_three_partitions() {
    if [ $# -ne 3 ]; then
      die "Usage: $0 <dev_base_node ex. /dev/mmcblk0, /dev/sda> <1st partition size> <2nd partition size>"
    fi

    basenode=$1
    partsize_1st=$2
    partsize_2nd=$3

    have_partition=`have_partition $basenode`
    if [ "$have_partition" = 'no' ]; then
      # check if the device size is big enough
      #input_size=`echo ${partsize_1st}*1024*1024+${partsize_2nd}*1024*1024 |bc`
      bnode=`echo $basenode |sed s'/\/dev\///'`
      actual_size=`cat /sys/block/${bnode}/size`
      actual_size=`echo ${actual_size}*1024 |bc`
      #if [[ $input_size -ge $actual_size ]]; then
      #  die "Device size is too small or Input size (1st+2nd) is too big!"
      #fi

      sector_size=`get_sector_size $basenode`
      end_of_1st_partition=`echo ${partsize_1st}*1024*1024/${sector_size} |bc`
      end_of_2nd_partition=`echo ${partsize_2nd}*1024*1024/${sector_size}+${end_of_1st_partition} |bc`
      echo "Making three partitions..."
      echo -e "p\nn\np\n1\n\n${end_of_1st_partition}\nn\np\n2\n\n${end_of_2nd_partition}\nn\np\n\n\n\na\n1\nt\n1\nc\np\nw\n" | fdisk $basenode
      # making initial fs
      ls ${basenode}* | grep ${basenode}p1 && (mkfs.vfat -F32 ${basenode}p1; mkfs.vfat -F32 ${basenode}p2; mkfs.vfat -F32 ${basenode}p3)
      ls ${basenode}* | grep ${basenode}1 && (mkfs.vfat -F32 ${basenode}1; mkfs.vfat -F32 ${basenode}2; mkfs.vfat -F32 ${basenode}3)
    else
      echo "Skipping creating partition in $basenode since there is at least one partition in it"
    fi
}

# This function is to check if blk device has at least on partition in it
have_partition() {
    basenode=$1
    match=`fdisk -l $basenode |grep -E "${basenode}p|${basenode}[1-9]+"`
    if [ "$match" = "" ]; then
      have_partition="no"
    else
      have_partition="yes"
    fi
    #ls ${basenode}* |grep -E "${basenode}1|${basenode}p1" > /dev/null && have_partition='yes' || have_partition='no'
    echo "$have_partition"
}

# This function is to get the sector size of blk device
get_sector_size() {
    basenode=$1
    bnode=`echo $basenode |sed s'/\/dev\///'`
    sector_size=`cat /sys/block/${bnode}/queue/hw_sector_size`
    echo $sector_size
}

# This function return DEVNODE with the biggest size.
#   If the partition is boot or rootfs partition, it will be skipped.
# Input: DEV_BASE_NODE: like /dev/mmcblk0 etc
#        device_type: like 'mmc', 'usb'
# It only tested on MMCSD and it should work on other block devices
#   like usb, ata etc.

find_part_with_biggest_size() {
  if [ $# -ne 2 ]; then
    die "Usage: $0 <dev_base_node like /dev/mmcblk0, /dev/sda> <device_type like mmc, usb>"
  fi

  DEV_BASE_NODE=$1
  DEVICE_TYPE=$2

  # check if fdisk works for this dev
  fdisk -l "$DEV_BASE_NODE" > fdisklog_$$ 2>&1 
  cat fdisklog_$$ |grep -i "fdisk doesn't support" > /dev/null
  if [ $? -ne 0 ]; then
    disklabel_type=`cat fdisklog_$$ |grep 'Disklabel type' |cut -d":" -f2 |sed 's/^ *//' |sed 's/ *$//' `
    if [ "gpt" == "$disklabel_type" ]; then
      parted -v > /dev/null && UTIL_TO_USE='parted' || (gdisk -v > /dev/null && UTIL_TO_USE='gdisk' || die "Do not know which util to check partition")
    else
      UTIL_TO_USE='fdisk'
    fi
  else
    # use parted or gdisk etc
    parted -v > /dev/null && UTIL_TO_USE='parted' || (gdisk -v > /dev/null && UTIL_TO_USE='gdisk' || die "Do not know which util to check partition")
  fi

  SIZE_BIGGEST=0
  TMP_IFS=$IFS
  IFS=$'\n'

  case "$UTIL_TO_USE" in

  fdisk)
    MATCH=`fdisk -l $DEV_BASE_NODE |grep -E "${DEV_BASE_NODE}p|${DEV_BASE_NODE}[1-9]+"`
    if [ "$MATCH" = "" ]; then
      die "fdisk does not show any partitions! Please check if the partitions really exist!"
    fi
    for i in $MATCH
    do
      LINE=$i
      FIELD_2ND=`echo "$LINE" | awk -F " " '{print $2}'`
      DEVNODE=`echo "$LINE" | awk -F " " '{print $1}'`
      SIZE=`echo "$LINE" | awk -F " " '{print $4}' | sed s/+$//`

      # skip bootable partition and rootfs partition with rootfs in it
      if [[ "$FIELD_2ND" != '*' ]]; then
        IS_ROOTFS=`is_part_rootfs "$DEVICE_TYPE" "$DEVNODE"` || die "error when calling is_part_rootfs: "$IS_ROOTFS" "
        if [ "$IS_ROOTFS" == "no" ]; then
          if [ $SIZE -gt $SIZE_BIGGEST ]; then
            SIZE_BIGGEST=$SIZE
            PART_DEVNODE="$DEVNODE"
          fi
        fi
      fi
    done
  ;;

  parted)
    case "$DEVICE_TYPE" in
    usb*|sata)
      PART_BASE_NODE="${DEV_BASE_NODE}"
    ;;
    *mmc)
      PART_BASE_NODE="${DEV_BASE_NODE}p"
    ;;
    *)
      die "device_type $DEVICE_TYPE is not supported"
    ;;
    esac
   
    MATCH=`ls ${PART_BASE_NODE}* |grep -Eo [[:digit:]]+$`
    for i in $MATCH
    do
      PART_NUM=$i
      DEVNODE="${PART_BASE_NODE}${PART_NUM}"

      LINE=`echo -e "print\nquit\n" |parted ${DEV_BASE_NODE} |grep -E "^ ${PART_NUM}"`
      SIZE=`echo "$LINE" |awk -F " " '{print $4}' |sed s'/[a-zA-Z].$//' `
      FLAG=`echo "$LINE" |awk -F " " '{print $7}'`
      PART_NAME=`echo "$LINE" |awk -F " " '{print $5}'`

      # if the partition flag contains 'boot', skip this partition
      if [[ "$FLAG" != *"boot"* ]] && [[ "$PART_NAME" != *"boot"* ]]; then
        IS_ROOTFS=`is_part_rootfs "$DEVICE_TYPE" "$DEVNODE"` || die "error when calling is_part_rootfs: "$IS_ROOTFS" "
        if [ "$IS_ROOTFS" == "no" ]; then
          if [ $SIZE -gt $SIZE_BIGGEST ]; then
            SIZE_BIGGEST=$SIZE
            PART_DEVNODE="${DEVNODE}"
          fi
        fi
      fi
    done
  ;;

  gdisk)
    die "Do not support gdisk yet"
  ;;
  
  *)
    die "Do not know which util to use"
  ;;

  esac

  IFS=$TMP_IFS

  if [ -z "$PART_DEVNODE" ]
  then
    
    die "Could not find the partition to test! Maybe all the existing partitions are either boot or rootfs partitions or the size is bigger than 32G. Please use fdisk to check the partitions!"
  fi  
  echo $PART_DEVNODE
}

# get size of the partition with PART_DEVNODE
# return size is in 'MBytes'
get_part_size_of_devnode() {
  PART_DEVNODE=$1
  PARTBYTES=`fdisk -l "$PART_DEVNODE" | grep "Disk "$PART_DEVNODE":" | awk '{print $5 }' `
  if [ $PARTBYTES -le 0 ]; then
    die "Could not get partition size from $PART_DEVNODE"
  fi

  PARTSIZE=$((${PARTBYTES}/MB))
  echo $PARTSIZE
}

# Get the partition is used for current rootfs
# Input: None
get_fs_root() {
  BOOTARGS=`cat /proc/cmdline`
  ROOT=`get_value_for_key "root" "$BOOTARGS" "="` || die "error getting root from proc cmdline: $ROOT"
  echo "$ROOT"
}

# Check if the partition is holding the root fs
# Input: partition devnode: like /dev/mmcblk0p1
#        device_type: to decide which fs to try to mount
is_part_rootfs(){
  if [ $# -ne 2 ]; then
    die "Usage: $0 <device_type like 'mmc', 'usb'> <device_node like /dev/mmcblk0p1, /dev/sda1>"
  fi
  DEVICE_TYPE=$1
  DEV_NODE=$2
  IS_MOUNTED="no"
  RTN="no"
  mount |grep "$DEV_NODE" > /dev/null && IS_MOUNTED="yes"
  if [ "$IS_MOUNTED" == "yes" ];then
    MNT_POINT=`mount |grep "$DEV_NODE" |cut -d" " -f3` 
  else
    MNT_POINT="/mnt/partition_${DEVICE_TYPE}_$$"
    do_cmd blk_device_do_mount.sh -n "$DEV_NODE" -d "$DEVICE_TYPE" -m "$MNT_POINT" > /dev/null 2>$1 
    mount |grep "$DEV_NODE" > /dev/null && IS_MOUNTED="yes" || die "Failed to mount $DEV_NODE when checking if it is rootfs partition"
    NEED_UMOUNT="yes"
  fi
  if [ -e "$MNT_POINT/etc" -a -e "$MNT_POINT/dev" ]; then
    RTN="yes"
  fi
  if [ "$NEED_UMOUNT" == "yes" ]; then
    do_cmd blk_device_umount.sh -m "$MNT_POINT" > /dev/null 2>$1
  fi
  echo "$RTN"
}

printout_model(){
  DEV_NODE=$1
  DEV_TYPE=$2
  case "$DEV_NODE" in
    *sd*)
      BASE_SD=`echo "$DEV_NODE" |sed "s/\/dev\///" |sed "s/[0-9]$//"` 
      do_cmd "cat /sys/block/$BASE_SD/device/model"
      ;;
    *)
      test_print_trc "model info is not available for non scsi devices."
      ;;
  esac
}

# find all available scsi drives
# Input: "usb" or "sata"
# Output: drives_found
find_all_scsi_drives() {
  SCSI_DEVICE=$1
  DRIVES_FOUND=""
  DRIVES=`fdisk -l |grep "Disk /dev/sd" | cut -b 13`
  for DRIVE in $DRIVES; do
    if [ -e /sys/block/sd"$DRIVE"/device/vendor ]; then
      VENDOR=`cat /sys/block/sd"$DRIVE"/device/vendor`
      RESULT=`echo $VENDOR | grep -i "ATA"`
      case $SCSI_DEVICE in
        sata)
          if [ -n "$RESULT" ]; then
            DRIVES_FOUND="${DRIVES_FOUND} $DRIVE"
          fi
        ;;
        usb)
          if [ -z "$RESULT" ]; then
            DRIVES_FOUND="${DRIVES_FOUND} $DRIVE"
          fi
        ;;
        all)
          DRIVES_FOUND="${DRIVES_FOUND} $DRIVE"
        ;;
      esac
    fi
  done
  if [ -n "$DRIVES_FOUND" ]; then
    echo "$DRIVES_FOUND"
  else
    # if could not find match, let user know
    echo "Could not find any device node for SCSI device!"
    exit 1
  fi
}
