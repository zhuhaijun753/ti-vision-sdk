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

# Print out the hw id (i.e hw:0,0) of all audio devices present on the board 

############################# Functions #######################################
usage()
{
cat <<-EOF >&2
        usage: ./${0##*/} [-d DEVICE_TYPE] [-t FUNC_TYPE]
        -d DEVICE_TYPE  audio device type like 'hdmi', 'am335x', etc. If
        this parameter is specified only the audio devices that include
        that string in their description will be returned if any
        -t FUNC_TYPE audio device function type 'play' or 'record'. If
        this parameter is not specified 'play' is used
EOF
exit 0
}

############################### CLI Params ###################################
while getopts  :d:t:h arg
do case $arg in
        d)  DEVICE_TYPE="$OPTARG";;
        t)  FUNC_TYPE="$OPTARG";;
        h)  usage;;
        :)  die "$0: Must supply an argument to -$OPTARG.";; 
        \?) die "Invalid Option -$OPTARG ";;
esac
done

: ${DEVICE_TYPE:=".*"}
: ${FUNC_TYPE:='play'}

if [ "$FUNC_TYPE" != 'play' -a "$FUNC_TYPE" != 'record' ]; then
  usage
fi

# Get $DEVICE_TYPE matching devices 
SOUND_CARDS=( `a${FUNC_TYPE} -l | grep -i card | grep -i "${DEVICE_TYPE}" | grep -o '[0-9]\+:' | cut -c 1` ) 

if [ ${#SOUND_CARDS[@]} -lt 2 ]
then
  echo "No ${DEVICE_TYPE} sound card found"
  exit 1
fi

for i in `seq 0 $((${#SOUND_CARDS[@]}/2 - 1))`;
do
  echo "hw:${SOUND_CARDS[$((i*2))]},${SOUND_CARDS[$((1 + i*2))]}"
done
