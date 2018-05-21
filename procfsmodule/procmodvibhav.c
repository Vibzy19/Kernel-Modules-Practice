#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/seq_file.h>

#define PROCFS_NAME "procawesomeiter"

int init_module(void);
void cleanup_module(void);

static int procfs_open(struct inode *, struct file *);

static void *my_seq_start(struct seq_file *, loff_t *);
static void *my_seq_next(struct seq_file *, void *, loff_t *);
static void my_seq_stop(struct seq_file *, void *);
static int my_seq_show(struct seq_file *, void *);

static const struct file_operations procfs_ops = {
	.owner = THIS_MODULE,
	.open = procfs_open,
	.release = seq_release,
	.read = seq_read,
	.llseek = seq_lseek	
};

static const struct seq_operations seq_ops = {
	.start = my_seq_start,
	.next = my_seq_next,
	.stop = my_seq_stop,
	.show = my_seq_show
};

static int procfs_open(struct inode *inode, struct file *file){
	int ret = seq_open(file, &seq_ops);
	return ret;
}


static void *my_seq_start(struct seq_file *sf, loff_t *pos){
	static unsigned long counter = 0;
	
	if(*pos == 0){
		return &counter;
	} 
	else{
		*pos = 0;
		return NULL;
	}
}

static void my_seq_stop(struct seq_file *sf, void *v){

}

static void *my_seq_next(struct seq_file *sf, void *v, loff_t *pos){
	unsigned long *tmp_v = (unsigned long *)v;
	*tmp_v++;
	*pos++;
	return NULL;	
}

static int my_seq_show(struct seq_file *sf, void *v){
	loff_t *spos = (loff_t *)v;
	seq_printf(sf, "%Ld \n", *spos);
	return 0;	
} 


int init_module(void){
	int ret = proc_create(PROCFS_NAME, 0, NULL, &procfs_ops);
	return ret;
}

void cleanup_module(void){
	remove_proc_entry(PROCFS_NAME,NULL);
}
