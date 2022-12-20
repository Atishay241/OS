#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

static int pid = 4; // pid of the process to print information for

int simple_init(void)
{
    struct task_struct *task;

    // find the task_struct for the specified pid
    
    for_each_process(task){
    // print the task's information if it was found
        if(task){
            if (task->pid == pid) {
                printk(KERN_INFO "Process information:\n");
                printk(KERN_INFO "  pid: %d\n", task->pid);
                printk(KERN_INFO "  name: %s\n", task->comm);
                printk(KERN_INFO "  priority: %d\n", task->prio);
                printk("User id: %d\n", task->cred->uid.val);
                printk("Group id: %d\n", task->group_leader->pid);
            } 
            }else {
                printk(KERN_INFO "Process with pid %d not found\n", pid);
            }
    }
    return 0;
}


void simple_exit(void)
{
    printk(KERN_INFO "Exiting process info module\n");
}

moeule_init(simple_init);
module_exit(simple_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("Atishay");