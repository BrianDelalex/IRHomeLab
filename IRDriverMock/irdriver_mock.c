// dummy_irdriver.c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>
#include <linux/sched/signal.h>

#include "irdriver_api.h"

#define DEVICE_NAME "irdriver"
#define CLASS_NAME  "irdriver_class"

#define MAX_CLIENTS 32

static dev_t dev_number;
static struct cdev ir_cdev;
static struct class *ir_class;

static pid_t registered_pids[MAX_CLIENTS];
static int client_count = 0;

static DEFINE_MUTEX(client_mutex);


// ------------------------------------------------------------
// IOCTL - Register client process
// ------------------------------------------------------------
static long ir_ioctl(struct file *file,
                     unsigned int cmd,
                     unsigned long arg)
{
    switch (cmd)
    {
        case CMD_REGISTER:
        {

            mutex_lock(&client_mutex);

            if (client_count >= MAX_CLIENTS)
            {
                mutex_unlock(&client_mutex);
                return -ENOMEM;
            }

            registered_pids[client_count] = arg;
            client_count++;

            pr_info("irdriver: registered pid=%d\n", (int)arg);

            mutex_unlock(&client_mutex);
            return 0;
        }

        default:
            return -EINVAL;
    }
}


// ------------------------------------------------------------
// WRITE - Simulate IR event
// ------------------------------------------------------------
static ssize_t ir_write(struct file *file,
                        const char __user *buf,
                        size_t len,
                        loff_t *offset)
{
    pr_info("irdriver: simulated IR event\n");

    int ret;
    int value;
    char *kbuf = kmalloc(sizeof(char) * (len + 1), GFP_KERNEL);
    if (!kbuf)
    {
        return -ENOMEM;
    }

    if (copy_from_user(kbuf, buf, len) != 0)
    {
        pr_info("irdriver: ir_write copy_from_user failed.\n");
        return -EINVAL;
    }
    ret = kstrtoint(kbuf, 10, &value);
    if (ret != 0) {
        return ret;
    }

    mutex_lock(&client_mutex);

    for (int i = 0; i < client_count; i++)
    {
        struct kernel_siginfo info;
        struct task_struct *t;

        memset(&info, 0, sizeof(struct kernel_siginfo));
        info.si_signo = SIGPOLL;
        info.si_code = SI_QUEUE;
        info.si_int = value;

        t = pid_task(find_vpid(registered_pids[i]), PIDTYPE_PID);
        if (t == NULL) {
            pr_info("ir_write: Can't find task with pid %d\n", registered_pids[i]);
        } else {
            if (send_sig_info(SIGPOLL, &info, t) < 0 )  {
                pr_info("Unable to send signal to %d\n", value);
            }
        }
    }

    mutex_unlock(&client_mutex);

    return len;
}


// ------------------------------------------------------------
// RELEASE - Optional cleanup when fd closed
// ------------------------------------------------------------
static int ir_release(struct inode *inode,
                      struct file *file)
{
    return 0;
}


// ------------------------------------------------------------
// FILE OPERATIONS
// ------------------------------------------------------------
static struct file_operations fops = {
    .owner          = THIS_MODULE,
    .unlocked_ioctl = ir_ioctl,
    .write          = ir_write,
    .release        = ir_release,
};


// ------------------------------------------------------------
// INIT
// ------------------------------------------------------------
static int __init ir_init(void)
{
    int ret;

    ret = alloc_chrdev_region(&dev_number, 0, 1, DEVICE_NAME);
    if (ret < 0)
        return ret;

    cdev_init(&ir_cdev, &fops);
    ir_cdev.owner = THIS_MODULE;

    ret = cdev_add(&ir_cdev, dev_number, 1);
    if (ret)
        goto unregister_region;

    ir_class = class_create("irdriver_mock_class");
    if (IS_ERR(ir_class))
    {
        ret = PTR_ERR(ir_class);
        goto del_cdev;
    }

    if (!device_create(ir_class, NULL,
                       dev_number, NULL,
                       DEVICE_NAME))
    {
        ret = -ENOMEM;
        goto destroy_class;
    }

    pr_info("irdriver: module loaded\n");
    return 0;

destroy_class:
    class_destroy(ir_class);
del_cdev:
    cdev_del(&ir_cdev);
unregister_region:
    unregister_chrdev_region(dev_number, 1);
    return ret;
}


// ------------------------------------------------------------
// EXIT
// ------------------------------------------------------------
static void __exit ir_exit(void)
{
    device_destroy(ir_class, dev_number);
    class_destroy(ir_class);
    cdev_del(&ir_cdev);
    unregister_chrdev_region(dev_number, 1);

    pr_info("irdriver: module unloaded\n");
}

module_init(ir_init);
module_exit(ir_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("BrianDelalex");
MODULE_DESCRIPTION("Dummy IR driver with ioctl registration and SIGPOLL notification");
