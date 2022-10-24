/* Copyright (c) 2013-2018, Linaro Limited
 * Copyright (c) 2021-2022, Nokia
 * All rights reserved.
 *
 * SPDX-License-Identifier:     BSD-3-Clause
 */

/**
 * @file
 *
 * ODP buffer descriptor - implementation internal
 */

#ifndef ODP_BUFFER_INTERNAL_H_
#define ODP_BUFFER_INTERNAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <odp/api/align.h>
#include <odp/api/buffer.h>

#include <odp_event_internal.h>

#include <stdint.h>

/* Type size limits number of flow IDs supported */
#define BUF_HDR_MAX_FLOW_ID 255

/* Internal buffer header */
typedef struct ODP_ALIGNED_CACHE odp_buffer_hdr_t {
	/* Common event header */
	_odp_event_hdr_t event_hdr;

	/* User area pointer */
	void *uarea_addr;

} odp_buffer_hdr_t;

static inline odp_buffer_hdr_t *_odp_buf_hdr(odp_buffer_t buf)
{
	return (odp_buffer_hdr_t *)(uintptr_t)buf;
}

#ifdef __cplusplus
}
#endif

#endif
