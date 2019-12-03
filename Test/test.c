/*
 * module1.c
 *
 * This is a first cut at a Linux driver module. This
 * module will simply announce its initialization and
 * cleanup to the system logs, which can be read via
 * a commandline such as:
 *
 * tail /var/log/syslog
 */


/*
 * special header files for Linux modules
 */

#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/time.h>
#include <linux/init.h>
#include <linux/stat.h>


/*
 * announce our software license and authorship
 */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Conestoga SET");


/*
 * static int __init initialize_my_module(void);
 *
 * This function will support the module initialization.
 * Note the use of the __init modifier for this function.
 */

static int __init initialize_my_module(void)
{
        printk(KERN_INFO "module1: Conestoga SET initialize_my_module() called.\n");
	printk(KERN_INFO "This is a test\n");
        return 0;
}

/*
 * static int __init cleanup_my_module(void);
 *
 * This function will support the module cleanup.
 * Note the use of the __exit modifier for this function.
 */

static void __exit cleanup_my_module(void)
{
        printk(KERN_INFO "module1: Conestoga SET cleanup_my_module() called.\n");
}


/*
 * these macros register the appropriate init and cleanup
 * functions that the Linux Kernel expects!
 */

module_init(initialize_my_module);
module_exit(cleanup_my_module);
