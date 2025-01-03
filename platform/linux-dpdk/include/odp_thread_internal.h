/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright (c) 2021 Nokia
 */

#ifndef ODP_THREAD_INTERNAL_H_
#define ODP_THREAD_INTERNAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * Read IDs of active ODP threads
 *
 * @param[out] ids          Thread ID array
 * @param      max_num      Maximum number of thread IDs to write
 *
 * @return Number of thread IDs written to the output array
 */
int _odp_thread_ids(unsigned int ids[], int max_num);

/**
 * Read current epoch value of thread mask all
 *
 * @return Thread mask all epoch value
 */
uint64_t _odp_thread_thrmask_epoch(void);

#ifdef __cplusplus
}
#endif
#endif
