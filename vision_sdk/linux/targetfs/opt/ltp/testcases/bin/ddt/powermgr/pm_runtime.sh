#!/bin/bash
#
# Test for runtime_pm
# Copyright (C) 2014 Texas Instruments Incorporated.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.

source "functions.sh"

# Get pm_runtime sysfs nodes for given device type
# $1: Device type, e.g. timer, i2c, mmc, etc.
get_pm_runtime_nodes() {
    local device_type=$1
    local nodes
    nodes=$(find /sys/devices -name power | grep $device_type)
    echo "${nodes[@]}"
}

# Check if pm_runtime is enabled for device_type given
# $1: Device type, e.g. timer, i2c, mmc, etc.
is_pm_runtime_enabled() {
    local device_type=$1
    for node in $(get_pm_runtime_nodes $device_type); do
        if [[ `cat $node/control` == 'auto' ]]; then
            echo "pm_runtime is enabled for $node"
            return 0
        fi
    done
    return 1
}

# Check if pm_runtime is allowed to suspend device_type given
# $1: Device type, e.g. timer, i2c, mmc, etc.
is_pm_runtime_suspending_device() {
    local device_type=$1
    for node in $(get_pm_runtime_nodes $device_type); do
        if [[ `cat $node/runtime_suspended_time` -gt 0 ]]; then
            echo "pm_runtime is suspending $node"
            echo "runtime_suspended_time: $(cat $node/runtime_suspended_time)"
            echo "runtime_active_time: $(cat $node/runtime_active_time)" 
            return 0
        fi
    done
    return 1
}


