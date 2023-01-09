#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>  
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/pid.h>
#include <linux/pid_namespace.h>
#include <linux/cred.h>
 
 
static int pidInt;
static struct pid *pStruct;
struct task_struct *presenttask;


module_param(pidInt, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

int init_module(void)
{
    pStruct = find_get_pid(pidInt);
    if (pStruct==NULL) {
       struct task_struct *task = current; 
        printk(KERN_NOTICE "Name of the Current Process %s, PID: %d", task->comm, task->pid);
        printk(KERN_NOTICE "User ID of the Current Process %d", task->cred->uid);
        printk(KERN_NOTICE "Group ID of the Current Process %d", task->tgid);
        printk(KERN_NOTICE "Command Path of the Current Process %s", task->comm);
    do{
        task = task->parent;
        printk(KERN_NOTICE "Name of the Parent Process %s, PID: %d", task->comm, task->pid);
        printk(KERN_NOTICE "User ID of the Parent Process %d", task->cred->uid);
        printk(KERN_NOTICE "Group ID of the Parent Process %d", task->tgid);
        printk(KERN_NOTICE "Command Path of the Parent Process %s", task->comm);

    } 
    while (task->pid != 0);
    return 0;
    }

    presenttask = pid_task(pStruct, PIDTYPE_PID);
    
    if (presenttask == NULL) {

        printk(KERN_NOTICE "Error Invalid PID\n" );
        return 0;
    }

    printk(KERN_NOTICE"PID: %d\n", presenttask->pid);
    printk(KERN_NOTICE"User ID: %d\n", presenttask->cred->uid);
    printk(KERN_NOTICE"PGID: %d\n", presenttask->cred->gid);
    printk(KERN_NOTICE"Command path: %s\n", presenttask->comm);

    return 0;
    
}
 
void cleanup_module(void) {
  printk(KERN_NOTICE"Exiting Module\n");
}

MODULE_LICENSE("Dual BSD/GPL");