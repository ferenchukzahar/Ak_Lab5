// SPDX-License-Identifier: Dual BSD/GPL
#include <linux/module.h>
#include <linux/moduleparam.h>
#include "hello1.h"

MODULE_AUTHOR("Zakhar Ferenchuk");
MODULE_DESCRIPTION("Hello2 module - parameter handling and caller");
MODULE_LICENSE("Dual BSD/GPL");

static uint count = 1;
module_param(count, uint, 0444);
MODULE_PARM_DESC(count, "Number of times to print Hello, world!");

static int __init hello2_init(void)
{
	uint i;

	if (count == 0 || (count >= 5 && count <= 10)) {
		pr_warn("Warning: count is %u\n", count);
	} else if (count > 10) {
		pr_err("Error: count is greater than 10 (count=%u)\n", count);
		return -EINVAL;
	}

	for (i = 0; i < count; i++) {
		print_hello();
	}

	return 0;
}

static void __exit hello2_exit(void)
{
}

module_init(hello2_init);
module_exit(hello2_exit);
