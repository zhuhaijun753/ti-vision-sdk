#!/bin/bash
#
# PM-QA validation test suite for the power management on Linux
#
# Copyright (C) 2011, Linaro Limited.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
#
# Contributors:
#     Daniel Lezcano <daniel.lezcano@linaro.org> (IBM Corporation)
#       - initial API and implementation
#

# URL : https://wiki.linaro.org/WorkingGroups/PowerManagement/Resources/TestSuite/PmQaSpecification#cpufreq_05

source /usr/bin/linaro-pm-qa-include/functions.sh

save_governors

trap restore_governors SIGHUP SIGINT SIGTERM

switch_ondemand() {
    local cpu=$1
    set_governor $cpu 'ondemand'
}

switch_conservative() {
    local cpu=$1
    set_governor $cpu 'conservative'
}

switch_userspace() {
    local cpu=$1
    set_governor $cpu 'userspace'
}

check_governor() {
    local cpu=$1
    local gov=$2

    if [ -d $CPU_PATH/$cpu/cpufreq/$gov ]; then
        GOV_PATH=$CPU_PATH/$cpu/cpufreq/$gov
    else
        GOV_PATH=$CPU_PATH/cpufreq/$gov
    fi
    check "'$gov' directory exists" "test -d $GOV_PATH"
}

supported=$(cat $CPU_PATH/cpu0/cpufreq/scaling_available_governors | grep "ondemand")
if [ -z "$supported" ]; then
    log_skip "ondemand not supported"
else
    for cpu in $(ls $CPU_PATH | grep "cpu[0-9].*"); do
        switch_ondemand $cpu
    done
    check_governor $cpu 'ondemand'
fi

supported=$(cat $CPU_PATH/cpu0/cpufreq/scaling_available_governors | grep "conservative")
if [ -z "$supported" ]; then
    log_skip "conservative not supported"
else
    for cpu in $(ls $CPU_PATH | grep "cpu[0-9].*"); do
        switch_conservative $cpu
    done
    check_governor $cpu 'conservative'
fi

supported=$(cat $CPU_PATH/cpu0/cpufreq/scaling_available_governors | grep "userspace")
if [ -z "$supported" ]; then
    log_skip "userspace not supported"
else
    for cpu in $(ls $CPU_PATH | grep "cpu[0-9].*"); do
        switch_userspace $cpu
    done

    check "'ondemand' directory is not there" "test ! -d $CPU_PATH/cpufreq/ondemand"
    check "'conservative' directory is not there" "test ! -d $CPU_PATH/cpufreq/conservative"
fi

# if more than one cpu, combine governors
nrcpus=$(ls $CPU_PATH | grep "cpu[0-9].*" | wc -l)
if [ $nrcpus -gt 1 ]; then
    affected=$(cat $CPU_PATH/cpu0/cpufreq/affected_cpus | grep 1)
    if [ -z $affected ]; then
        switch_ondemand cpu0
        switch_conservative cpu1
        check_governor cpu0 'ondemand'
        check_governor cpu1 'conservative'
    else
        log_skip "combine governors not supported"
    fi
fi

restore_governors
test_status_show
