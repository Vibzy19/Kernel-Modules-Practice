#include <chardev.h>

#include <stdio.h>
#include <stdlib.h>
#include <fnctl.h>
#include <unistd.h>
#include <sys/ioctl.h>

ioctl_set_msg(int, char *);
ioctl_get_msg(int);
ioctl_get_nth_byte(int);

ioctl_set_msg(int file_desc, char *message){
	int ret;

	ret = ioctl(file_desc, IOCTL_SET_MSG, message);
	if (ret < 0){
		printf("ioctl_set_msg failed:%d \n", ret);
		exit(-1);
	}
}

ioctl_get_msg(int file_desc){
	int ret;
	char message[100];

	ret = ioctl(file_desc,IOCTL_GET_MSG, message);
	if(ret<0){
		printf("ioctl_get_msg failed:%d \n", ret);
		exit(-1);
	}

	printf("get_msg message : %s \n",message);
}

ioctl_get_nth_byte(int file_desc){
	int i;
	char c;

	printf("get_nth_byte message :");

	int i = 0;
	do {
		c = ioctl_get_nth_byte(file_desc,IOCTL_GET_NTH_BYTE,i++)
		if(c<0){
			printf("ioctl_get_nth_byte failed with %d \n",i);
			exit(-1);
		}
	} while(c!=0);
	putchar("\n");
}

main(){
	int file_desc, ret_val;
	char *msg = "Message passed by ioctl \n";	

	file_desc = open(DEVICE_FILE_NAME, 0);
	
	ioctl_set_msg(file_desc,msg);
	ioctl_get_msg(file_desc);
	ioctl_get_nth_byte(file_desc);
	
	close(file_desc);
}
