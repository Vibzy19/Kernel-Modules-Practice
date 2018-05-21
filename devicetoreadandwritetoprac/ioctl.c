#include <chardev.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <fnctl.h>
#include <stdlib.h> 
#include <unistd.h>

ioctl_set_msg(int, char *);
ioctl_get_msg(int);
ioctl_get_nth_byte(int);

ioctl_set_msg(int file_desc. char *message){
	int ret;
	
	ret = ioctl(file_desc, IOCTL_SET_MSG, message);
	if(ret < 0){
		printk(KERN_INFO "IOCTL_GET_MSG not working due to error %d", ret);
		exit(-1);
	}
	else{
		printk(KERN_INFO "IOCTL_GET_MSG working with return value %d", ret);
	}
}

ioctl_get_msg(int file_desc){
        int ret;
	char message[100];

        ret = ioctl(file_desc, IOCTL_GET_MSG, message);
        if(ret < 0){
                printk(KERN_INFO "IOCTL_GET_MSG not working due to error %d", ret);
                exit(-1);
        }
        else{
                printk(KERN_INFO "IOCTL_GET_MSG working with return value %d", ret);
        }
	printf("get_msg : %s \n",message);
}

ioctl_get_nth_byte(int file_desc){
	char c
	int i;
	
	printf("get nth byte : ");

	i = 0;
	do{
		c = ioctl(file_desc,IOCTL_GET_NTH_BYTE,i++)
        	if(ret < 0){
                	printk(KERN_INFO "IOCTL_GET_MSG not working due to error %d", ret);
                	exit(-1);
		}	
        	else{
                	printk(KERN_INFO "IOCTL_GET_MSG working with return value %d", ret);
        	}	

	}while(c!=0);
	putchar("\n");
}

main(){
	int file_desc, ret_val;
	char *mesg = "Message passed by IOCTL \n";
	
	file_desc = open(DEVICE_NAME,0);

	ioctl_set_msg(file_desc, msg);
	ioctl_get_msg(file_desc);
	ioctl_get_nth_byte(file_desc);

	close(file_desc);
}
