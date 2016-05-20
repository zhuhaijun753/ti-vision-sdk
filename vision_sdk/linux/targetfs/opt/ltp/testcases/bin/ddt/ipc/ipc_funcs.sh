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

# This function saves the existing firmware (if any) to <fw name>.orig
# Inputs:
#    $*: names of all the firmware files to be saved
save_firmware()
{
  for __fw in $*
  do
    if [ -f ${__fw} -a ! -h ${__fw} ]
    then
      mv $__fw ${__fw}.orig
    fi
  done
}

# This fucntion sets up the appropriate firmware that will be loaded on the
# remote processor for IPC related test
# Inputs:
#    $1: name pattern of the firmware files that should be loaded. These files
#        should be located in /lib/firmware folder of the file system
setup_firmware()
{
  local __fw_pattern=$1
  local __fw_dir='/lib/firmware'
  pushd ${__fw_dir}
  local __fw_files=$(find $__fw_dir -type f -name "${__fw_pattern}" -exec basename {} \;)
  echo "Found $__fw_files fw files..."
  case $MACHINE in
    dra7xx-evm|am57xx*)
      save_firmware dra7-dsp1-fw.xe66 dra7-dsp2-fw.xe66 dra7-ipu2-fw.xem4 dra7-ipu1-fw.xem4
      for __fw in $__fw_files
      do
        echo "Setting up $__fw ..."
        case $__fw in
          *dsp1*)
            ln -sf $__fw dra7-dsp1-fw.xe66
            ;;
          *dsp2*)
            ln -sf $__fw dra7-dsp2-fw.xe66
            ;;
          *ipu1*)
            ln -sf $__fw dra7-ipu1-fw.xem4
            ;;
          *ipu2*)
            ln -sf $__fw dra7-ipu2-fw.xem4
            ;;
          *)
            echo "File $__fw did not contain processor tag"
            ;;
        esac
      done
    ;;
    am43xx*|am335x*)
      save_firmware rproc-pru0-fw rproc-pru1-fw
      for __fw in $__fw_files
      do
        echo "Setting up $__fw ..."
        case $__fw in
          *pru0*)
            ln -sf $__fw rproc-pru0-fw
            ;;
          *pru1*)
            ln -sf $__fw rproc-pru1-fw
            ;;
          *)
            echo "File $__fw did not contain processor tag"
            ;;
        esac
      done
    ;;
    am57xx*)
      save_firmware am57xx-pru1_0-fw am57xx-pru1_1-fw am57xx-pru2_0-fw am57xx-pru2_1-fw
      for __fw in $__fw_files
      do
        echo "Setting up $__fw ..."
        case $__fw in
          *pru0*)
            ln -sf $__fw am57xx-pru1_0-fw
            ln -sf $__fw am57xx-pru2_0-fw
            ;;
          *pru1*)
            ln -sf $__fw am57xx-pru1_1-fw
            ln -sf $__fw am57xx-pru2_1-fw
            ;;
          *)
            echo "File $__fw did not contain processor tag"
            ;;
        esac
      done
    ;;
    *)
      echo "Machine ${MACHINE} not supported"
      popd
      return 1
      ;;           
  esac
  sync
  popd
}

# Function to rmod the rpmsg loadable modules so that new firmware can 
# be loaded in the remote processors
rm_ipc_mods()
{
  local __modules=(rpmsg_rpc rpmsg_proto rpmsg_client_sample virtio_rpmsg_bus omap_remoteproc remoteproc)
  
  kill_lad
  
  for __mod in ${__modules[@]}
  do
    modprobe -r ${__mod}
  done
}

# Function to insmod the modules require to run RPMSG. Without parameters
# Inputs:
#   $*: (Optional) Additional modules to load, i.e 'rpmsg_rpc', 'rpmsg_proto', etc
ins_ipc_mods()
{
  
  local __modules=(remoteproc omap_remoteproc virtio_rpmsg_bus)
  
  if [ $# -gt 0 ];
  then
    __modules+=($*)
  fi
  
  for __mod in ${__modules[@]}
  do
    insmod.sh ${__mod}
  done
}

# Function to obtain the number of remote processors in the SOC.
# Returns:
#  The number of remote processors in the SOC
get_num_remote_procs()
{
  case $SOC in
    *dra7xx)
      echo 4
      ;;
    *j6eco)
      echo 3
      ;;
    *)
      echo "SOC ${SOC} not supported"
      return 1
      ;;           
  esac
}

# Function to obtain valid rproc ids for a given SOC.
# Inputs:
#   $1: The number of remote processor to get ids for
# Returns:
#  The proc ids of the remote procs
get_rpmsg_proto_rproc_ids()
{ 
  case $SOC in
    *dra7xx)
      rids=( `seq 1 4` )
      ;;
    *j6eco)
      rids=( 1 2 4 )
      ;;
    *)
      echo "SOC ${SOC} not supported"
      return 1
      ;;           
  esac
  echo ${rids[@]::$1}
}

# Funtion to run the RPMSG-RPC test
# Inputs:
#   -p: The number of remote processor to use in the test
#   -f: (Optional) The function or part of the function name to execute
#       in the remote processor. Defaults to _triple
#   -m: (Optional) int used to trigger an MMU fault while running the test.
#       0:Fault on first message, 1: Fault on middle messsage 
#       2: Fault on last message 
#   -s: (Optional) the time in sec after which the test should be killed,
#       or if -a is specified after -c command will be sent.
#       This option is useful to test stability, 
#   -c: (Optional) command to send after time -s seconds
# Returns, 0 if the test passed, 1 if the single processor test failed,
#          2 if the multiprocessors test failed, or 3 if both single and
#          multiprocessor test fails
rpmsg_rpc_test()
{
  local __num_procs=$1
  local __kill_time=0
  local __result=0
  local __instances=10
  local __f_name='_triple'
  local __msg_num=''
  local __multiproc_cmds=("" "" "" "")
  local __rpc_cmd='test_rpmsg_rpc'
  local __test_log
  local __num_match
  local __command
  local __add_cmd=''
  OPTIND=1 
  local _iterations
  while getopts :p:c:f:s:m: arg
  do case $arg in
    p)  __num_procs="$OPTARG";;
    s)  __kill_time="$OPTARG";;
    f)  __f_name="$OPTARG";;
    m)  __msg_num="-m $OPTARG";;
    c)  __add_cmd="$OPTARG";;

    \?)  test_print_trc "Invalid Option -$OPTARG ignored." >&2
    return 1
    ;;
  esac
  done
  
  for __rproc in `seq 0 $((__num_procs - 1))`
  do
    __multiproc_cmds[0]="${__multiproc_cmds[0]} & $__rpc_cmd -t $((__rproc % 3 + 1)) -c $__rproc -x $__instances -l $__instances -f $__f_name $__msg_num"
    __multiproc_cmds[1]="${__multiproc_cmds[1]} & $__rpc_cmd -t 1 -c $__rproc -x $__instances -l $__instances -f $__f_name $__msg_num"
    __multiproc_cmds[2]="${__multiproc_cmds[2]} & $__rpc_cmd -t 2 -c $__rproc -x $__instances -l $__instances -f $__f_name $__msg_num"
    __multiproc_cmds[3]="${__multiproc_cmds[3]} & $__rpc_cmd -t 3 -c $__rproc -x $__instances -l $__instances -f $__f_name $__msg_num"
    for __t_type in `seq 1 3`
    do
      __command="$__rpc_cmd -t $__t_type -c $__rproc -x $__instances -l $__instances -f $__f_name $__msg_num"
      if [ $__kill_time -gt 0 ]
      then
        __command="${__command} & sleep $__kill_time; "
        if [ "$__add_cmd" != '' ]
        then
          __command="${__command} $__add_cmd"
        else
          __command="${__command} killall $__rpc_cmd"
        fi 
      fi
      echo $__command
      __test_log=$(eval $__command)
      __num_match=$(echo -e "$__test_log" | grep -c -i "TEST STATUS: PASSED")
      if [ $__num_match -ne 1 ]
      then
        __result=1
        echo -e "${__test_log}\nTest $__t_type failed for proc ${__rproc}"
      else
        echo "Test $__t_type passed for proc $__rproc"
      fi
    done
  done

  if [ $__num_procs -gt 1 ]
  then
    for __cmd in "${__multiproc_cmds[@]}"
    do
      if [ $__kill_time -gt 0 ]
      then
        __cmd="${__cmd} & sleep $__kill_time;"
        if [ "$__add_cmd" != '' ]
        then
          __cmd="${__cmd} $__add_cmd"
        else
          __cmd="${__cmd} killall $__rpc_cmd" 
        fi
      fi
      echo ${__cmd:3}
      __test_log=$(eval ${__cmd:3})
      __num_match=$(echo -e "$__test_log" | grep -i -c "TEST STATUS: PASSED")
      echo -e "$__num_match processors passed..."
      if [ $__num_match -ne $__num_procs ]
      then
        let "__result|=2"
        echo -e "$__test_log\nTest failed for ${__cmd:3}"
      else
        echo -e "Test passed for ${__cmd:3}"
      fi
    done
  fi
  
  return $__result
}

#Function to stop the ipc lad daemon
kill_lad()
{
  case $MACHINE in
    *dra7xx-evm|*am57xx-evm)
      killall lad_dra7xx
      ;;
    *)
      echo "Machine ${MACHINE} not supported"
      return 1
      ;;           
  esac
  
  return 0
}

#Function to start the ipc lad daemon
start_lad()
{
  case $MACHINE in
    *dra7xx-evm|*am57xx-evm)
      lad_dra7xx
      ;;
    *)
      echo "Machine ${MACHINE} not supported"
      return 1
      ;;           
  esac
}

# Funtion to run the RPMSG-RPC test
# Inputs:
#   $1: The number of remote processor to use in the test
#   $2: (Optional) number of loops. Default 5000
#   $3: (Optional) the time in sec after which the test should be killed,
#       or if $4:* is specified after $4 will be sent.
#       This option is useful to test stability, 
#   $4:*: (Optional) command to send after time $3 seconds
# Returns, 0 if the test passed, 1 if the single processor test failed,
#          2 if the multiprocessors test failed, or 3 if both single and
#          multiprocessor test fails
rpmsg_proto_msgqapp_test()
{
  local __num_procs=$1
  local __kill_time=0
  local __result=0
  local __loops=5000
  local __multiproc_cmd=""
  local __ipc_cmd='MessageQApp'
  local __test_log
  local __num_match
  local __command
  local __rproc_ids=$(get_rpmsg_proto_rproc_ids $__num_procs)
  
  if [ $# -gt 1 ]
  then
    __loops=$2
  fi
  if [ $# -gt 2 ]
  then
    __kill_time=$3
  fi
  
  for __rproc in $__rproc_ids
  do
    __multiproc_cmd="$__multiproc_cmd & $__ipc_cmd $__loops $__rproc"
    __command="$__ipc_cmd $__loops $__rproc"
    if [ $__kill_time -gt 0 ]
    then
      __command="${__command} & sleep $__kill_time; "
      if [ $# -gt 3 ]
      then
        __command="${__command} ${@:4}"
      else
        __command="${__command} killall $__ipc_cmd"
      fi 
    fi
    echo $__command
    __test_log=$(eval $__command)
    __num_match=$(echo -e "$__test_log" | grep -c -i 'Sample\s\+application\s\+successfully\s\+completed')
    if [ $__num_match -ne 1 ]
    then
      __result=1
      echo -e "${__test_log}\nTest failed for proc ${__rproc}"
    else
      echo "Test passed for proc $__rproc"
    fi
  done

  if [ $__num_procs -gt 1 ]
  then
    if [ $__kill_time -gt 0 ]
    then
      __multiproc_cmd="${__multiproc_cmd} & sleep $__kill_time; "
      if [ $# -gt 3 ]
      then
        __multiproc_cmd="${__multiproc_cmd} ${@:4}"
      else
        __multiproc_cmd="${__multiproc_cmd} killall $__ipc_cmd"
      fi
    fi
    echo ${__multiproc_cmd:3}
    __test_log=$(eval ${__multiproc_cmd:3})
    __num_match=$(echo -e "$__test_log" | grep -i -c 'Sample\s\+application\s\+successfully\s\+completed')
    echo -e "$__num_match processors passed..."
    if [ $__num_match -ne $__num_procs ]
    then
      let "__result|=2"
      echo -e "$__test_log\nTest failed for ${__multiproc_cmd:3}"
    else
      echo -e "Test passed for ${__multiproc_cmd:3}"
    fi
  fi
  
  return $__result
}

# Funtion to run the RPMSG-RPC test
# Inputs:
#   $1: The number of remote processor to use in the test
#   $2: (Optional) number of loops. Default 5000
#   $3: (Optional) payload size. Default 8
# Returns, 0 if perf data was collected, 1 if not
rpmsg_proto_msgqbench_test()
{
  local __num_procs=$1
  local __result=0
  local __loops=5000
  local __payload_sz=8
  local __multiproc_cmd=""
  local __ipc_cmd='MessageQBench'
  local __test_log
  local __num_match
  local __command
  local __rproc_ids=$(get_rpmsg_proto_rproc_ids $__num_procs)
  
  if [ $# -gt 1 ]
  then
    __loops=$2
  fi
  if [ $# -gt 2 ]
  then
    __payload_sz=$3
  fi
  
  for __rproc in $__rproc_ids
  do
    __multiproc_cmd="$__multiproc_cmd & $__ipc_cmd $__loops $__payload_sz $__rproc"
    __command="$__ipc_cmd $__loops  $__payload_sz $__rproc"
    echo $__command
    __test_log=$(eval $__command)
    __num_match=$(echo -e "$__test_log" | grep -c -i 'Avg\s\+round\s\+trip\s\+time:')
    if [ $__num_match -ne 1 ]
    then
      __result=1
      echo -e "${__test_log}\nTest failed for proc ${__rproc}"
    else
      echo "Test passed for proc $__rproc"
      test_print_trc " ROUNDTRIP_TIME | $(echo -e "$__test_log" | grep -i 'Avg\s\+round\s\+trip\s\+time:')"
    fi
  done

  if [ $__num_procs -gt 1 ]
  then
    echo ${__multiproc_cmd:3}
    __test_log=$(eval ${__multiproc_cmd:3})
    __num_match=$(echo -e "$__test_log" | grep -c -i 'Avg\s\+round\s\+trip\s\+time:')
    echo -e "$__num_match processors passed..."
    if [ $__num_match -ne $__num_procs ]
    then
      let "__result|=2"
      echo -e "$__test_log\nTest failed for ${__multiproc_cmd:3}"
    else
      echo -e "Test passed for ${__multiproc_cmd:3}"
      test_print_trc " ROUNDTRIP_TIME_MULTI | $(echo -e "$__test_log" | grep -i 'Avg\s\+round\s\+trip\s\+time:')"
    fi
  fi
  
  return $__result
}

# Funtion to run the RPMSG-RPC test
# Inputs:
#   $1: (Optional) The number of threads to use in the test. 
#       Default 10
#   $2: (Optional) number of loops. Default 5000
#   $3: (Optional) the time in sec after which the test should be killed,
#       or if $4:* is specified after $4 will be sent.
#       This option is useful to test stability, 
#   $4:*: (Optional) command to send after time $3 seconds
# Returns, 0 if succesful, 1 otherwise
rpmsg_proto_msgqmulti_test()
{
  local __kill_time=0
  local __result=0
  local __loops=5000
  local __num_threads=10
  local __ipc_cmd='MessageQMulti'
  local __test_log
  local __num_match
  local __command
  if [ $# -gt 0 ]
  then
    __num_threads=$1
  fi
  if [ $# -gt 1 ]
  then
    __loops=$2
  fi
  if [ $# -gt 2 ]
  then
    __kill_time=$3
  fi
  
  __command="$__ipc_cmd $__num_threads $__loops"
  if [ $__kill_time -gt 0 ]
  then
    __command="${__command} & sleep $__kill_time; "
    if [ $# -gt 3 ]
    then
      __command="${__command} ${@:4}"
    else
      __command="${__command} killall $__ipc_cmd"
    fi 
  fi
  echo $__command
  __test_log=$(eval $__command)
  __num_match=$(echo -e "$__test_log" | grep -c -i 'pingThreadFxn\s\+successfully\s\+completed')
  if [ $__num_match -ne $__num_threads ]
  then
    __result=1
    echo -e "${__test_log}\nTest failed..."
  else
    echo "Test passed..."
  fi
  
  return $__result
}

# Funtion to run the RPMSG client sample test based on the kernel's 
# samples/rpmsg module
# Inputs:
#   $1: Number of remote proccessors in the SOC
#   $2: (Optional) Number of trials. Defaults to 1 
# Returns, 0 if succesful, 1 otherwise
rpmsg_client_sample_test()
{
  local __result=0
  local __test_log
  local __num_goodbye
  local __num_procs=$1
  local __command
  local __loops=1
  
  if [ $# -gt 1 ]
  then
    __loops=$2
  fi
  
  for idx in `seq 1 $__loops`
  do
    __test_log=$(dmesg -c > /dev/null && insmod ddt/rpmsg_client_sample.ko && sleep 3 && dmesg)
    __num_match=$(echo -e "$__test_log" | grep -c -i 'rpmsg[0-9]\+: incoming msg 100')
    __num_goodbye=$(echo -e "$__test_log" | grep -c -i 'rpmsg[0-9]\+: goodbye!')
    if [ $__num_match -ne 1 -o  $__num_goodbye -ne $(($__num_procs * 2)) ]
    then
      __result=$((__result + 1))
      echo -e "${__test_log}\nTest failed..."
    else
      echo "Test passed..."
    fi
    rmmod rpmsg_client_sample
  done
  
  return $__result
}

# Funtion obtain the command that may be used to trigger a recovery
# event
# Returns:
#   A string containing the command to trigger the driver's crash
#   recovery mechanism 
rpmsg_recovery_event()
{
  local __mbox_q_addr
  local __command=""
  
  case $MACHINE in
    *dra7xx-evm|*am57xx-evm)
      __mbox_q_addr=('0x48840044' '0x48840050' '0x48842044' '0x48842050')
      ;;
    *)
      echo "Machine ${MACHINE} not supported"
      return 1
      ;;           
  esac
  
  for __mb_addr in ${__mbox_q_addr[@]}
  do
    __command="$__command && devmem2 $__mb_addr w 0xffffff02"
  done
  
  echo ${__command:3}
}

# Function to bind/unbind the prus
# Inputs:
#   $1: action to perform, either "bind" or "unbind"
#   $2:* devices to bind/unbind
toggle_prus()
{
  local __driver_sysfs='/sys/bus/platform/drivers/pru-rproc'

  for __pru in ${@:2}
  do
    echo "${1}ing $__pru ..."
    echo "$__pru" > ${__driver_sysfs}/$1
  done
}

# Funtion to obtain the list of pru devices
# Returns the list of PRU devices based on the MACHINE var value
list_prus()
{
  case $MACHINE in
    am43xx*)
      echo "54434000.pru0 54438000.pru1"
    ;;
    am335x*)
      echo "4a334000.pru0 4a338000.pru1"
    ;;
    am57xx*)
      echo "4b234000.pru0 4b238000.pru1 4b2b4000.pru0 4b2b8000.pru1"
    ;;
    *)
      echo "Machine ${MACHINE} not supported"
    ;;
  esac
}
