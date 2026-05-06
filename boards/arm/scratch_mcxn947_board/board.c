/*
 * Copyright 2024 Custom
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/init.h>
#include <zephyr/sys/printk.h>

void board_early_init_hook(void)
{
    /* Empty implementation for now */
}


static int board_init(void)
{
	printk("Board Initialized\n");
	return 0;
}

SYS_INIT(board_init, PRE_KERNEL_1, 0);
