// SPDX-License-Identifier: Dual BSD/GPL
#include <linux/module.h>
#include <linux/slab.h>
#include "hello1.h"

MODULE_AUTHOR("Zakhar Ferenchuk");
MODULE_DESCRIPTION("Hello1 module - list logic and export");
MODULE_LICENSE("Dual BSD/GPL");

static LIST_HEAD(event_list);

void print_hello(void)
{
	struct hello_event *event;

	event = kmalloc(sizeof(*event), GFP_KERNEL);
	if (!event) {
		pr_err("Memory allocation failed\n");
		return;
	}

	event->time_before = ktime_get();
	pr_info("Hello, world!\n");
	event->time_after = ktime_get();

	list_add_tail(&event->list, &event_list);
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
	return 0;
}

static void __exit hello1_exit(void)
{
	struct hello_event *cursor, *tmp;

	list_for_each_entry_safe(cursor, tmp, &event_list, list) {
		ktime_t duration = ktime_sub(cursor->time_after, cursor->time_before);
		pr_info("Time taken: %lld ns\n", ktime_to_ns(duration));
		list_del(&cursor->list);
		kfree(cursor);
	}
}

module_init(hello1_init);
module_exit(hello1_exit);
