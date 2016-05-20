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

# Run PCI Ethernet tests

source "common.sh"

############################# Functions #######################################
usage()
{
cat <<-EOF >&2
  usage: ./${0##*/} [-i ETH_IFACE] [-a ACTION]  
  -a ACTION the ethernet test to be run .
  -h Help   print this usage
EOF
exit 0
}

############################### CLI Params ###################################
while getopts  :i:a:h arg
do case $arg in
  i)  ETH_IFACE="$OPTARG";;
  a)  ACTION="$OPTARG";;
  h)  usage;;
  :)  test_print_trc "$0: Must supply an argument to -$OPTARG." >&2
      exit 1
      ;;
  \?) test_print_trc "Invalid Option -$OPTARG ignored." >&2
      usage
      exit 1
      ;;
esac
done

############################ DEFAULT Params #######################
test_print_trc "ACTION: $ACTION"
test_print_trc "ETH_IFACE: $ETH_IFACE"

# prepare pci eth test
iface_list=`get_active_eth_interfaces.sh`; 
echo "${iface_list[@]}"; 
if [ -z "${ETH_IFACE}" ];then
  ETH_IFACE=`pci_eth_search_device.sh 'pci'` || die "error getting pcie eth interface name";  
  echo "PCI eth iface: $ETH_IFACE"; 
fi
iface_config="iface ${ETH_IFACE} inet dhcp"; 
grep "$iface_config" /etc/network/interfaces || ( echo "$iface_config" >> /etc/network/interfaces ); 
for interface in ${iface_list[@]}; do 
  do_cmd "ifdown $interface"; 
done; 
do_cmd "ifup ${ETH_IFACE}"; 
host=`get_eth_gateway.sh "-i ${ETH_IFACE}"` || die "error getting eth gateway address";
echo "host:${host}"

#run eth tests
if [ -n "$ACTION" ]; then
  eval "$ACTION"
fi

# clean up after pci eth test
do_cmd "ifdown $ETH_IFACE"; 
for interface in ${iface_list[@]}; do 
  do_cmd "ifup $interface"; 
done

# end of script
