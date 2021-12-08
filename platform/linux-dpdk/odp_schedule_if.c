/* Copyright (c) 2018, Linaro Limited
 * Copyright (c) 2021, Nokia
 * All rights reserved.
 *
 * SPDX-License-Identifier:     BSD-3-Clause
 */

#include <odp/autoheader_internal.h>

#include <odp_schedule_if.h>
#include <odp_init_internal.h>
#include <odp_debug_internal.h>
#include <odp_global_data.h>

/* Required for _ODP_SCHED_ID_EVENTDEV */
#include <odp_eventdev_internal.h>

#include <stdlib.h>
#include <string.h>

extern const schedule_fn_t _odp_schedule_sp_fn;
extern const schedule_api_t _odp_schedule_sp_api;

extern const schedule_fn_t _odp_schedule_basic_fn;
extern const schedule_api_t _odp_schedule_basic_api;

extern const schedule_fn_t _odp_schedule_eventdev_fn;
extern const schedule_api_t _odp_schedule_eventdev_api;

const schedule_fn_t *_odp_sched_fn;
const schedule_api_t *_odp_sched_api;
int _odp_sched_id;

uint64_t odp_schedule_wait_time(uint64_t ns)
{
	return _odp_sched_api->schedule_wait_time(ns);
}

int odp_schedule_capability(odp_schedule_capability_t *capa)
{
	return _odp_sched_api->schedule_capability(capa);
}

void odp_schedule_config_init(odp_schedule_config_t *config)
{
	memset(config, 0, sizeof(*config));

	_odp_sched_api->schedule_config_init(config);
}

int odp_schedule_config(const odp_schedule_config_t *config)
{
	int ret;
	odp_schedule_config_t defconfig;

	if (odp_global_rw->schedule_configured) {
		ODP_ERR("Scheduler has been configured already\n");
		return -1;
	}

	if (!config) {
		odp_schedule_config_init(&defconfig);
		config = &defconfig;
	}

	ret = _odp_sched_api->schedule_config(config);

	if (ret >= 0)
		odp_global_rw->schedule_configured = 1;

	return ret;
}

odp_event_t odp_schedule(odp_queue_t *from, uint64_t wait)
{
	ODP_ASSERT(odp_global_rw->schedule_configured);

	return _odp_sched_api->schedule(from, wait);
}

int odp_schedule_multi(odp_queue_t *from, uint64_t wait, odp_event_t events[],
		       int num)
{
	ODP_ASSERT(odp_global_rw->schedule_configured);

	return _odp_sched_api->schedule_multi(from, wait, events, num);
}

int odp_schedule_multi_wait(odp_queue_t *from, odp_event_t events[], int num)
{
	return _odp_sched_api->schedule_multi_wait(from, events, num);
}

int odp_schedule_multi_no_wait(odp_queue_t *from, odp_event_t events[], int num)
{
	return _odp_sched_api->schedule_multi_no_wait(from, events, num);
}

void odp_schedule_pause(void)
{
	_odp_sched_api->schedule_pause();
}

void odp_schedule_resume(void)
{
	_odp_sched_api->schedule_resume();
}

void odp_schedule_release_atomic(void)
{
	_odp_sched_api->schedule_release_atomic();
}

void odp_schedule_release_ordered(void)
{
	_odp_sched_api->schedule_release_ordered();
}

void odp_schedule_prefetch(int num)
{
	_odp_sched_api->schedule_prefetch(num);
}

int odp_schedule_min_prio(void)
{
	return _odp_sched_api->schedule_min_prio();
}

int odp_schedule_max_prio(void)
{
	return _odp_sched_api->schedule_max_prio();
}

int odp_schedule_default_prio(void)
{
	return _odp_sched_api->schedule_default_prio();
}

int odp_schedule_num_prio(void)
{
	return _odp_sched_api->schedule_num_prio();
}

odp_schedule_group_t odp_schedule_group_create(const char *name,
					       const odp_thrmask_t *mask)
{
	return _odp_sched_api->schedule_group_create(name, mask);
}

int odp_schedule_group_destroy(odp_schedule_group_t group)
{
	return _odp_sched_api->schedule_group_destroy(group);
}

odp_schedule_group_t odp_schedule_group_lookup(const char *name)
{
	return _odp_sched_api->schedule_group_lookup(name);
}

int odp_schedule_group_join(odp_schedule_group_t group,
			    const odp_thrmask_t *mask)
{
	return _odp_sched_api->schedule_group_join(group, mask);
}

int odp_schedule_group_leave(odp_schedule_group_t group,
			     const odp_thrmask_t *mask)
{
	return _odp_sched_api->schedule_group_leave(group, mask);
}

int odp_schedule_group_thrmask(odp_schedule_group_t group,
			       odp_thrmask_t *thrmask)
{
	return _odp_sched_api->schedule_group_thrmask(group, thrmask);
}

int odp_schedule_group_info(odp_schedule_group_t group,
			    odp_schedule_group_info_t *info)
{
	return _odp_sched_api->schedule_group_info(group, info);
}

void odp_schedule_order_lock(uint32_t lock_index)
{
	_odp_sched_api->schedule_order_lock(lock_index);
}

void odp_schedule_order_unlock(uint32_t lock_index)
{
	_odp_sched_api->schedule_order_unlock(lock_index);
}

void odp_schedule_order_unlock_lock(uint32_t unlock_index, uint32_t lock_index)
{
	_odp_sched_api->schedule_order_unlock_lock(unlock_index, lock_index);
}

void odp_schedule_order_lock_start(uint32_t lock_index)
{
	_odp_sched_api->schedule_order_lock_start(lock_index);
}

void odp_schedule_order_lock_wait(uint32_t lock_index)
{
	_odp_sched_api->schedule_order_lock_wait(lock_index);
}

void odp_schedule_print(void)
{
	_odp_sched_api->schedule_print();
}

int _odp_schedule_init_global(void)
{
	const char *sched = getenv("ODP_SCHEDULER");

	if (sched == NULL || !strcmp(sched, "default"))
		sched = _ODP_SCHEDULE_DEFAULT;

	ODP_PRINT("Using scheduler '%s'\n", sched);

	if (!strcmp(sched, "basic")) {
		_odp_sched_id = _ODP_SCHED_ID_BASIC;
		_odp_sched_fn = &_odp_schedule_basic_fn;
		_odp_sched_api = &_odp_schedule_basic_api;
	} else if (!strcmp(sched, "sp")) {
		_odp_sched_id = _ODP_SCHED_ID_SP;
		_odp_sched_fn = &_odp_schedule_sp_fn;
		_odp_sched_api = &_odp_schedule_sp_api;
	} else if (!strcmp(sched, "eventdev")) {
		_odp_sched_id = _ODP_SCHED_ID_EVENTDEV;
		_odp_sched_fn = &_odp_schedule_eventdev_fn;
		_odp_sched_api = &_odp_schedule_eventdev_api;
	} else {
		ODP_ABORT("Unknown scheduler specified via ODP_SCHEDULER\n");
		return -1;
	}

	return _odp_sched_fn->init_global();
}

int _odp_schedule_term_global(void)
{
	return _odp_sched_fn->term_global();
}