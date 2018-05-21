#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/stat.h>

int number1 = 10;
int number2 = 11;
int sum = 0;

module_param(number1,int,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
module_param(number2,int,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
module_param(sum,int,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

static int __init mod_init(void){
	
	sum = number1+number2;
	printk(KERN_INFO "Adding %d and %d to get %d \n",number1,number2,sum);
	return 0;
}

static void __exit mod_exit(void){

	printk(KERN_INFO "Exiting the awesome parameter module \n");
}

module_init(mod_init);
module_exit(mod_exit);
