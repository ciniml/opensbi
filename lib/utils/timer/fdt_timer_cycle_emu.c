/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2021 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#include <libfdt.h>
#include <sbi/sbi_error.h>
#include <sbi/sbi_timer.h>
#include <sbi_utils/fdt/fdt_helper.h>
#include <sbi_utils/timer/fdt_timer.h>


#if __riscv_xlen == 32
static u64 get_cycles(void)
{
	u32 lo, hi, tmp;
	__asm__ __volatile__("1:\n"
			     "rdcycleh %0\n"
			     "rdcycle %1\n"
			     "rdcycleh %2\n"
			     "bne %0, %2, 1b"
			     : "=&r"(hi), "=&r"(lo), "=&r"(tmp));
	return ((u64)hi << 32) | lo;
}
#else
static u64 get_cycles(void)
{
	unsigned long n;

	__asm__ __volatile__("rdcycle %0" : "=r"(n));
	return n;
}
#endif


static u64 cycle_timer_value(void)
{
	return get_cycles();
}

static struct sbi_timer_device cycle_timer = {
	.name = "cycle-timer",
	.timer_value = cycle_timer_value,
};

static int timer_cycle_timer_cold_init(void *fdt, int nodeoff,
				  const struct fdt_match *match)
{	
	int rc = 0;
	rc = fdt_parse_timebase_frequency(fdt, &cycle_timer.timer_freq);
	if (rc)
		return rc;
	sbi_timer_set_device(&cycle_timer);
	return 0;
}
static int timer_cycle_timer_warm_init()
{
	return 0;
}

static const struct fdt_match timer_cycle_timer_match[] = {
	{ .compatible = "riscv,cycle-timer" },
	{ },
};

struct fdt_timer fdt_timer_cycle_timer = {
	.match_table = timer_cycle_timer_match,
	.cold_init = timer_cycle_timer_cold_init,
	.warm_init = timer_cycle_timer_warm_init,
	.exit = NULL,
};
