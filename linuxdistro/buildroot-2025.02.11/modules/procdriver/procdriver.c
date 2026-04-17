#include <linux/module.h>
#include <linux/init.h>
#include <linux/printk.h>
#include <linux/proc_fs.h>
#include <linux/errno.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Estudante");
MODULE_DESCRIPTION("Proc Driver");
MODULE_VERSION("0.0.1");

#define PROCFS_NAME "helloworld"


static ssize_t procfile_read(struct file *filep, char __user *buffer, size_t len, loff_t *offset)
{
    static int reads = 0;
    char greeting[] = "HelloWorld!";

    pr_info("Calling procfile_read\n");

    if (*offset > 0)
        return 0;

    char tmpbuf[256];
    sprintf(tmpbuf, "%s, %d reads", greeting, ++reads);
    int tmplen = strlen(tmpbuf);

    int error_count = copy_to_user(buffer, tmpbuf, tmplen);
    if (error_count != 0) {
        pr_alert("Failed to send %d characters to the user\n", error_count);
        return -EFAULT;
    }

    *offset = tmplen;
    return tmplen;
}

static struct proc_ops proc_file_fops = {
    .proc_read = procfile_read
};

static struct proc_dir_entry *proc_file;

static int procdrv_init(void)
{
    pr_info("Inserting the Proc module\n");

    proc_file = proc_create(PROCFS_NAME, 0644, NULL, &proc_file_fops);
    if (proc_file == NULL) {
        pr_alert("Could not initialize /proc/%s\n", PROCFS_NAME);
        return -ENOMEM;
    }
    pr_info("/proc/%s created\n", PROCFS_NAME);

    return 0;
}

static void procdrv_exit(void)
{
    proc_remove(proc_file);
    pr_info("Removed the Proc module\n");
}

module_init(procdrv_init);
module_exit(procdrv_exit);