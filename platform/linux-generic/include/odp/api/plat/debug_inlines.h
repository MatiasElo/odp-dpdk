/* Copyright (c) 2014-2018, Linaro Limited
 * Copyright (c) 2020-2022, Nokia
 * All rights reserved.
 *
 * SPDX-License-Identifier:     BSD-3-Clause
 */

/**
 * @file
 *
 * ODP Debug inlines
 *
 * @warning These definitions are not part of ODP API, they are for
 * implementation internal use only.
 */

#ifndef ODP_DEBUG_INLINES_H_
#define ODP_DEBUG_INLINES_H_

#include <odp/autoheader_external.h>

#include <odp/api/hints.h>
#include <odp/api/init.h>

#include <odp/api/plat/thread_inline_types.h>

/** @cond _ODP_HIDE_FROM_DOXYGEN_ */

#ifdef __cplusplus
extern "C" {
#endif

/* Avoid "ISO C99 requires at least one argument for the "..."  in a variadic
 * macro" errors when building with 'pedantic' option. */
#pragma GCC system_header

extern odp_log_func_t ODP_PRINTF_FORMAT(2, 3) _odp_log_fn;
extern odp_abort_func_t _odp_abort_fn;

#define _ODP_LOG_FN(level, fmt, ...) \
	do { \
		if (_odp_this_thread && _odp_this_thread->log_fn) \
			_odp_this_thread->log_fn(level, fmt, ##__VA_ARGS__); \
		else \
			_odp_log_fn(level, fmt, ##__VA_ARGS__); \
	} while (0)

/**
 * ODP LOG macro.
 */
#define _ODP_LOG(level, fmt, ...) \
		 _ODP_LOG_FN(level, "%s:%d:%s():" fmt, __FILE__, \
		 __LINE__, __func__, ##__VA_ARGS__)

/**
 * Runtime assertion-macro - aborts if 'cond' is false.
 */
#define _ODP_ASSERT(cond) \
	do { if ((ODP_DEBUG == 1) && (!(cond))) { \
		_ODP_ERR("%s\n", #cond); \
		_odp_abort_fn(); } \
	} while (0)

/*
 * Print debug message to log, if ODP_DEBUG_PRINT flag is set (ignores CONFIG_DEBUG_LEVEL).
 */
#define _ODP_DBG(fmt, ...) \
	do { \
		if (ODP_DEBUG_PRINT == 1) \
			_ODP_LOG(ODP_LOG_DBG, fmt, ##__VA_ARGS__);\
	} while (0)

/**
 * Log error message.
 */
#define _ODP_ERR(fmt, ...) \
	_ODP_LOG(ODP_LOG_ERR, fmt, ##__VA_ARGS__)

/**
 * Log abort message and then stop execution (by default call abort()).
 * This function should not return.
 */
#define _ODP_ABORT(fmt, ...) \
	do { \
		_ODP_LOG(ODP_LOG_ABORT, fmt, ##__VA_ARGS__); \
		_odp_abort_fn(); \
	} while (0)

/**
 * Log print message when the application calls one of the ODP APIs
 * specifically for dumping internal data.
 */
#define _ODP_PRINT(fmt, ...) \
	_ODP_LOG_FN(ODP_LOG_PRINT, fmt, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

/** @endcond */

#endif