# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2026 Nokia
#

##########################################################################
# Enable/disable 1 GHz time counter frequency assumption
##########################################################################
time_freq_1ghz=no
AC_ARG_ENABLE([time-freq-1ghz],
	      [AS_HELP_STRING([--enable-time-freq-1ghz],
			      [assume 1 GHz time counter frequency for fast time conversions]
			      [[default=disabled] (linux-dpdk)])],
	      [time_freq_1ghz=$enableval])

if test x$time_freq_1ghz = xyes; then
    AC_DEFINE([_ODP_TIME_FREQ_1GHZ], [1],
	      [Define to 1 to assume 1 GHz time counter frequency])
fi
