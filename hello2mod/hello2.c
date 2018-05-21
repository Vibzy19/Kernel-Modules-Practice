#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>


static int __init hello2init(void){

	printk(KERN_INFO "Loading Module \n");
	return 0;
}

static void __exit hello2exit(void){

	printk(KERN_INFO "Module exiting \n");
}


module_init(hello2init);
module_exit(hello2exit);
