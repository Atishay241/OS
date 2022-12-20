#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

static int pid = 1; // pid of the process to print information for

int init_module(void)
{
    struct task_struct *task;

    // find the task_struct for the specified pid
    rcu_read_lock();
    task = find_task_by_vpid(pid);
    rcu_read_unlock();

    // print the task's information if it was found
    if (task) {
        printk(KERN_INFO "Process information:\n");
        printk(KERN_INFO "  pid: %d\n", task->pid);
        printk(KERN_INFO "  name: %s\n", task->comm);
        printk(KERN_INFO "  state: %ld\n", task->state);
        printk(KERN_INFO "  priority: %d\n", task->prio);
    } else {
        printk(KERN_INFO "Process with pid %d not found\n", pid);
    }

    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Exiting process info module\n");
}
