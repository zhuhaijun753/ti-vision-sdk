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
                                                                               
# @desc Invokes station stop script from wl18xx demo folder                    
# @params none                                              
# succesful when sta_stop.sh is completed successfully                                
source "common.sh"  # Import do_cmd(), die() and other functions               
                                                                               
demo_folder=`find / -name sta_stop.sh`
[ -n "$demo_folder" ] || die "Unable to find sta_stop.sh script. Please ensure all station scripts are present in file system."
demo_folder=${demo_folder%"/sta_stop.sh"}
nohup "$demo_folder"/sta_stop.sh &
sleep 10
