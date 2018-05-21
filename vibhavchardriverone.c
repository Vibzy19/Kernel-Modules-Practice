#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#include <linux/fs.h>
void cleanup_module(void);
int init_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *,size_t ,loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

#define SUCCESS 0 
#define DEVICE_NAME "vibhavcharacterdriverone"
#define BUF_LEN 80


static int Major;
static int Device_Open = 0;
static char msg[BUF_LEN];
static char *msg_Ptr;


static struct file_operations fops = {

	.read = device_read,
	.release = device_release,
	.open = device_open,
	.write = device_write

};


int init_module(void){

	Major = register_chrdev(0,DEVICE_NAME,&fops);
	if(Major < 0){
		printk(KERN_ALERT "ERR Character device %s not registered %d\n",DEVICE_NAME,Major);
		return Major;
	}
	printk(KERN_INFO "Character device %s registered with Major %d \n", DEVICE_NAME, Major);
	return 0;
	
}

void cleanup_module(void){

	unregister_chrdev(Major,DEVICE_NAME);

}

static int device_open(struct inode *inode, struct file *file){
	
	static int counter = 0;

	if(Device_Open){
		return -EBUSY;
	}

	Device_Open++;
	sprintf(msg, "I have already said %d times that I am open \n", counter);
	msg_Ptr = msg;
	try_module_get(THIS_MODULE);	

	return SUCCESS;
}

static int device_release(struct inode *inode, struct file *file){
	
	Device_Open--;
	module_put(THIS_MODULE);	

	return 0;
}

static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset){
	
	int bytes_read = 0;
	if(*msg_Ptr==0){
		return 0;
	}

	while(length && *msg_Ptr){
		put_user(*(msg_Ptr++), buffer++);
		length--;
		bytes_read--;
	}
	
	return bytes_read;		

}

static ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t *off){

	printk(KERN_ALERT "Operation not supported \n");
	return -EINVAL;

}
