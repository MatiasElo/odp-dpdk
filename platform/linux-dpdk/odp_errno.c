/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright (c) 2015-2018 Linaro Limited
 */

#include <odp/api/errno.h>
#include <string.h>
#include <stdio.h>
#include <odp_debug_internal.h>
#include <rte_errno.h>

int odp_errno(void)
{
	return rte_errno;
}

void odp_errno_zero(void)
{
	rte_errno = 0;
}

void odp_errno_print(const char *str)
{
	if (str != NULL)
		_ODP_PRINT("%s %s\n", str, strerror(rte_errno));
	else
		_ODP_PRINT("%s\n", strerror(rte_errno));
}

const char *odp_errno_str(int errnum)
{
	return strerror(errnum);
}
