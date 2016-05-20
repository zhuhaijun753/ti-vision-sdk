# Filename: Makefile
#
# This file is the makefile for building SBL (Secondary Bootloader).
#
#   Copyright (C) 2014 Texas Instruments Incorporated
#
#   All rights reserved. Property of Texas Instruments Incorporated.
#   Restricted rights to use, duplicate or disclose this code are
#   granted through contract.
#
#   The program may not be used without the written permission
#   of Texas Instruments Incorporated or against the terms and conditions
#   stipulated in the agreement under which this program has been
#   supplied.
#******************************************************************************

ifeq ($(SOC),$(filter $(SOC), tda2xx tda2ex tda3xx))
    include makefile_$(SOC).mk
endif
