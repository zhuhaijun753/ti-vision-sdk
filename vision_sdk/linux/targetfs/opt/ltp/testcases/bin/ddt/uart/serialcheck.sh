#! /bin/sh
############################################################################### 
# Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
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

# @desc Test UART ports using git://git.breakpoint.cc/bigeasy/serialcheck.git

source "common.sh"  # Import do_cmd(), die() and other functions

#### Functions definitions ####
usage()
{
    echo "usage: ./${0##*/} [-r UART_RATE] [-l LOOPS]"
    exit 1
}

check_requirements() {
    which serialcheck || die "serialcheck binary is not available. Please install it"
}

create_test_file() {
    temp_test_file=`mktemp`
    dd if=/dev/urandom of=$temp_test_file count=1 bs=4096
}

get_uart_ports() {
for i in ${ARRAY[@]}; do
    if [ `cat $i` -ne 0 ]; then
        UART_PORTS=("${UART_PORTS[@]}" /dev/`echo $i | cut -d'/' -f 5 `)
    fi
done
}

filter_out_used_ports() {
    for i in ${UART_PORTS[@]}; do
        lsof | grep $i &> /dev/null || PORTS_TO_TEST=("${PORTS_TO_TEST[@]}" $i)
    done
}

run_serial_check() {
    for i in ${PORTS_TO_TEST[@]}; do    
        echo ''; echo "Testing $i at $UART_RATE $UART_LOOPS times" 
        serialcheck -b $UART_RATE -d $i -f $temp_test_file -l $UART_LOOPS -m d -k || die "TEST FAILED"
    done
}


#### Process input parameters ####
while getopts  :r:l:h arg
do case $arg in
        r)      UART_RATE="$OPTARG";;
        l)      UART_LOOPS="$OPTARG";;
        h)      usage;;
        :)      die "$0: Must supply an argument to -$OPTARG.";;
        \?)     die "Invalid Option -$OPTARG ";;
esac
done

# Default values 
: ${UART_RATE:=115200}
: ${UART_LOOPS:=5}

PORTS_TO_TEST=();
UART_PORTS=();
ARRAY=(`find /sys/class/tty/*/uartclk`);


#### Test Sequence ####
check_requirements
create_test_file
get_uart_ports
filter_out_used_ports
run_serial_check 

