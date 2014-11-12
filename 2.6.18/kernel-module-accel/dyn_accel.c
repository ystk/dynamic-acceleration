#include <linux/config.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/screen_info.h>

MODULE_DESCRIPTION("Dynaccel");
MODULE_AUTHOR("TOSHIBA CORPORATION");
MODULE_LICENSE("GPL");

#define DSINFO_PROCFS_NAME "accel"
#define PROCFS_MAX_SIZE	   1024

static struct proc_dir_entry *accel_proc_file;

static char          procfs_buffer[PROCFS_MAX_SIZE];
static unsigned long procfs_buffer_size = 0;

static int accel_init_module(void);
static void accel_cleanup_module(void);

static int accel_read(char *buffer,
                       char **buffer_location,
                       off_t offset, int buflen, int *eof, void *data)
{
        size_t size;

        size = sizeof(struct screen_info);

        /* copy data */
        if (offset > 0){
                return 0;
        }else{
                memcpy(buffer, (char *)&screen_info, size);
                return size;
        }
}


	int ret;
	
	printk(KERN_INFO "procfile_read (/proc/%s) called\n", PROCFS_NAME);
	
	if (offset > 0) {
		/* we have finished to read, return 0 */
		ret  = 0;
	} else {
		/* fill the buffer, return the buffer size */
		memcpy(buffer, procfs_buffer, procfs_buffer_size);
		ret = procfs_buffer_size;
	}

	return ret;
}



static int accel_init_module()
{
	accel_proc_file = create_proc_entry(ACCEL_PROCFS_NAME, 0644, NULL);

	if (accel_proc_file == NULL) {
		remove_proc_entry(ACCEL_PROCFS_NAME, &proc_root);
		printk(KERN_ALERT "Error: Could not initialize /proc/%s\n",
		       ACCEL_PROCFS_NAME);
		return -ENOMEM;
	}
        
	accel_proc_file->read_proc = accel_read;
	accel_proc_file->write_proc = accel_write;
	accel_proc_file->owner     = THIS_MODULE;
	accel_proc_file->uid 	    = 0;
	accel_proc_file->gid       = 0;
	accel_proc_file->size 	    = sizeof(struct screen_info);
        
	return 0;
}

static void accel_cleanup_module()
{
	remove_proc_entry(ACCEL_PROCFS_NAME, &proc_root);
}

module_init(accel_init_module);
module_exit(accel_cleanup_module);
