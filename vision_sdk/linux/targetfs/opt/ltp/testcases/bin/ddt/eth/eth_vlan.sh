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
source "common.sh"  # Import do_cmd(), die() and other functions

############################# Functions #######################################
                                                                                
########################### REUSABLE TEST LOGIC ############################### 
# Usage information: eth_vlan.sh	-v <num_of_vlans> 
#					-l <num_of_iterations> 
#                                 	-d <duration of ping in seconds>
#                                 	-p <packetsize for ping in bytes>   
#################################################################################

################################################################################
# Cleanup function for use before the test exits
################################################################################
do_cleanup()
{ 
	for interface in `ls /proc/net/vlan/|grep eth`
  	do 
    		vconfig rem $interface
  	done
}

# Forcing cleanup in case there are some vlans from a previous failed test
do_cleanup
p_vlans=5
p_iterations=10
p_duration=10
p_pktsize=64
OFS=$IFS
while getopts ":v:l:d:p" opt; do
	  case $opt in 
  		v)
    			p_vlans=$OPTARG
    		;;
  		l)
    			p_iterations=$OPTARG
    		;;
  		d)
    			p_duration=$OPTARG
    		;;
  		p)
    			p_pktsize=$OPTARG
  		esac
done

# check for all eth interfaces supported and create an array
j=0
for device in `find /sys/class/net/*eth*`
do 
	operstate='down'
  	interface=`echo $device | cut -c16-`
  	operstate=`cat /sys/class/net/$interface/operstate`
  	int_name[j]=$interface
  	j+=1
done

# for each eth interface, find the corresponding gateway
for (( j=0; j < ${#int_name[@]}; j++ ))
do
	for interface in ${int_name[@]}
 	do
   		ifdown $interface
 	done

	ifup ${int_name[j]}
 	eth_gateway[j]=`get_eth_gateway.sh -i ${int_name[j]}` || die "Error getting eth gateway for ${int_name[j]}"
	ifdown ${int_name[j]}
 
	for interface in ${int_name[@]}
 	do
   		ifup $interface
 	done
done

# now run the test based on command-line parameters
for (( i=0; i < ${#int_name[@]}; i++ ))
do
	ifdown ${int_name[i]}
	do_cmd "ifup ${int_name[i]}"
	for (( k=1; k<$p_vlans; k++ ))
	do
		do_cmd "vconfig add ${int_name[i]} $k"
    		rm nohup.out
    		nohup ping ${eth_gateway[$i]} -s $p_pktsize -w $p_duration & 
        	pid=$! 
    		# wait for ping process to be completed
    		if [ "x$pid" != "x" ]                                               
    		then                                                              
      			wait ${pid}                                                       
      			rc=$?                                                           
      			if [ "$rc" -ne "0" ]                                            
      			then                                                            
        			die "Ping Process failed"                                                         
        		break                                                         
      			fi                                                              
    		fi                                                                
    		result=`cat nohup.out | grep " 0% packet loss"`
    		if [[ ! -n "$result" ]] 
    		then   
      			die "${int_name[i]} - Ping resulted in packet loss"
    		fi
    		result=`cat nohup.out | grep "Network is unreachable"`
    		if [[ -n "$result" ]] 
    		then   
      			die "${int_name[i]} - Network is unreachable"
    		fi
	done # for each vlan
  done # for each interface

for (( i=0; i < ${#int_name[@]}; i++ ))
do
	for (( k=1; k<$p_vlans; k++ ))
    	do
		do_cmd "vconfig rem ${int_name[i]}.$k"
    		rm nohup.out
    		nohup ping ${eth_gateway[$i]} -s $p_pktsize -w $p_duration & 
        	pid=$! 
    		# wait for ping process to be completed
    		if [ "x$pid" != "x" ]                                               
    		then                                                              
      			wait ${pid}                                                       
      			rc=$?                                                           
      			if [ "$rc" -ne "0" ]                                            
      			then                                                            
        			die "Ping Process failed"                                                         
        			break                                                         
      			fi                                                              
    		fi                                                                
    		result=`cat nohup.out | grep " 0% packet loss"`
    		if [[ ! -n "$result" ]] 
    		then   
      			echo "$result"
      			die "${int_name[i]} - Ping resulted in packet loss"
    		fi
    		result=`cat nohup.out | grep "Network is unreachable"`
    		if [[ -n "$result" ]] 
    		then   
      			echo "$result"
      			die "${int_name[i]} - Network is unreachable"
    		fi
    	done # for each vlan
done # for each interface

IFS=$OFS
