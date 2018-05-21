#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#include "chardev.h"
#define DEVICE_NAME "educateddevice"
#define BUF_LEN 80
#define SUCCESS 0

static int Device_Open = 0;
static char msg[BUF_LEN];
static char *msg_ptr;

int init_module(void);
void cleanup_module(void);

static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char __user *, int, loff_t *);
static ssize_t device_write(struct file *, const char __user *, int , loff_t *);
static int device_ioctl(struct inode *, struct file *, unsigned int, unsigned long);

static struct file_operations educateddevice_fops ={
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release,
	.ioctl = device_ioctl,
	.owner = THIS_MODULE
};

static int device_open(struct inode *inode, struct file *file){
	printk(KERN_INFO "Device_Open=%d",Device_Open);
	Device_Open++;
	if(Device_Open){
		printk(KERN_INFO "Device already initialized %s", DEVICE_NAME);
		return -EBUSY;
	}
	msg_ptr = msg;
	try_module_get(THIS_MODULE);
	return 0;
}

static int device_release(struct inode *inode, struct file *file){
	if(Device_Open == 1){	
		printk(KERN_INFO "Releasing the device !! \n");
		Device_Open--;
	}
	module_put(THIS_MODULE);
}

static ssize_t device_read(struct file *filp, char __user *buf, int length, loff_t *offset){
	int bytes_read = 0;
	if(*msg_ptr == 0){
		return 0;
	}
	while(length && *msg_ptr){
		put_user(*(msg_ptr),(buf)++);
		length--;
		bytes_read++;
	}
	return bytes_read;
}

static ssize_t device_write(struct file *filp, const char __user *buf, int length, loff_t *offset){
	int bytes_read;
	for(bytes_read=0; bytes_read<BUF_LEN && bytes_read<length; bytes_read++){
		get_user(msg[bytes_read],buf+bytes_read); //Get one byte per iteration and write it to the buf+bytes_read address
	}
	msg_ptr = msg;
	return bytes_read;
}

int device_ioctl(struct inode *inode, struct file *filp, unsigned int ioctl_num, unsigned long ioctl_param){

	int i;
	char *temp;
	char ch;

	switch(ioctl_num){
		case IOCTL_SET_MSG:
			temp = (char *)ioctl_param;
			get_user(ch, temp);
			for(i=0; i<BUF_LEN;i++){
				get_user(ch, temp);
			}
			device_write(filp, (char *)temp, i,0);
			break;
		case IOCTL_GET_MSG:
			i = device_read(filp, (char *)ioctl_param, 99, 0);
			put_user("\0",(char *)ioctl_param + i);
			break;
		case IOCTL_GET_NTH_BYTE:
			return msg[ioctl_param];
			break;
	}
	return 0;
}

int init_module(void){
        int ret;

        ret = register_chrdev(MAJOR_NUMBER, DEVICE_NAME, &chardev_fops);
        if(ret < 0){
                printk(KERN_ALERT "Character device not registered. Returning %d \n", MAJOR_NUMBER);
                return ret;
        }
        printk(KERN_INFO "Character Device registered with Major Number %d \n", MAJOR_NUMBER);
        printk(KERN_INFO "Create a character device using the following command :- \n");
        printk(KERN_INFO "# mknod %s -c %d 0 \n", DEVICE_FILE_NAME, MAJOR_NUMBER);

        return 0;
}

void cleanup_module(void){
        printk(KERN_INFO "Character Device unregistered with Major Number %d \n", MAJOR_NUMBER);
        unregister_chrdev(MAJOR_NUMBER, DEVICE_NAME);
}

