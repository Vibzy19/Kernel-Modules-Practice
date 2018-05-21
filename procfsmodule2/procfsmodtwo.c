#include <linux/proc_fs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/seq_file.h>

#define PROC_NAME "procfsmodtwo"

int init_module(void);
void cleanup_module(void);

static int my_seq_open(struct inode *, struct file *);
static void *my_seq_start(struct seq_file *, loff_t *); 
static void *my_seq_next(struct seq_file *, void *, loff_t *);
static void my_seq_stop(struct seq_file *, void *);
static void my_seq_show(struct seq_file *, void *);

static struct file_operations procfs_fops = {
	.owner = THIS_MODULE,
	.open = my_seq_open,
	.read = seq_read,
	.release = seq_release,
	.llseek = seq_lseek
};

static struct seq_operations procfs_seqops = {
	.start = my_seq_start, 
	.next = my_seq_next,
	.stop = my_seq_stop,
	.show = my_seq_show
};

static int my_seq_open(struct inode *inode, struct file *file){
	int ret = seq_open(file,&procfs_seqops);
	if(ret == 0){
		printk(KERN_INFO "seq_file initialized with seq_operations \n");
	}
	else {
		printk(KERN_ALERT "seq_file couldn't be initialized qith the defined seq_ops , ERR %d \n",ret);
	}
	return ret;
}

static void *my_seq_start(struct seq_file *seqf, loff_t *pos){
	static unsigned long counter = 0;
	if(*pos == 0){
		printk(KERN_INFO "Starting a new sequence \n");
		return &counter;
	}
	else{
		printk(KERN_INFO "The sequence has ended \n");
		*pos=0;
		return NULL;
	}
}

static void *my_seq_next(struct seq_file *seqf, void *v, loff_t *pos){
	unsigned long *tmp_v = (unsigned long*)v;
	*tmp_v++;
	*pos++;
	return NULL;
}

static void my_seq_stop(struct seq_file *seqf, void *v){}

static void my_seq_show(struct seq_file *seqf, void *v){
	loff_t *spos = (loff_t *)v;
	seq_printf(seqf, "%Ld \n",*spos);
	return 0;
}

int init_module(void){
	int ret  = proc_create(PROC_NAME, 0, NULL, &procfs_fops);	
	printk(KERN_INFO "Initializing procfsmodtwo .. \n");
	return ret;
}

void cleanup_module(void){
	remove_proc_entry(PROC_NAME, NULL);
	printk(KERN_INFO "Removing procfsmodtwo .. \n");
}
