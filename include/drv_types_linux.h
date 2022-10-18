/******************************************************************************
 *
 * Copyright(c) 2007 - 2017 Realtek Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 *****************************************************************************/
#ifndef __DRV_TYPES_LINUX_H__
#define __DRV_TYPES_LINUX_H__

#include <linux/version.h>
#include <linux/kthread.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 1, 0)
#include <linux/random.h>
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 13, 0) && LINUX_VERSION_CODE < KERNEL_VERSION(5, 17, 0)
    #ifdef set_kthread_struct
        #undef set_kthread_struct
    #endif

    #undef kthread_run
	#define kthread_run(threadfn, data, namefmt, ...)			   \
({									   \
	struct task_struct *__k						   \
		= kthread_create(threadfn, data, namefmt, ## __VA_ARGS__); \
	if (!IS_ERR(__k)) {						   \
		set_kthread_struct(__k);				\
		wake_up_process(__k);				   \
	}											\
	__k;								   \
})
#endif

#endif
