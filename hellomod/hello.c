#include <linux/module.h>
#include <linux/kernel.h>

int init_module(void){

	printk(KERN_INFO "Loading Character Module ! \n");
	return 0;

}

void cleanup_module(void){

	printk(KERN_INFO "All the world is a stage ! \n");

}
