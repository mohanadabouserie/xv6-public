#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"

#include "stat.h"

extern struct {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;
int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int sys_gettime(void)
{
  return gettime();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int sys_procinfo(void)
{
  return procinfo();	
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int sys_setpriority(void) {
  int pid;
  int pr;
  if (argint(0, &pid) < 0 || argint(1, &pr) < 0)
    return -1;
  struct proc *p;
  int old_priority = -1;
  // Find the process with pid
  acquire(&ptable.lock);
  for (p = ptable.proc; p < &ptable.proc[NPROC]; p++) {
    if (p->pid == pid && p->state != UNUSED) {
      old_priority = p->priority;
      p->priority = pr;  // Set the new priority
      break;
    }
  }
  release(&ptable.lock);
  return old_priority;
}

int sys_printptable(void) {
  struct proc *p;
  char *state;

  acquire(&ptable.lock);
  for (p = ptable.proc; p < &ptable.proc[NPROC]; p++) {
    if (p->state == UNUSED)
      continue;

    // Convert state to a string
    switch (p->state) {
      case EMBRYO: state = "EMBRYO"; break;
      case SLEEPING: state = "SLEEPING"; break;
      case RUNNABLE: state = "RUNNABLE"; break;
      case RUNNING: state = "RUNNING"; break;
      case ZOMBIE: state = "ZOMBIE"; break;
      default: state = "UNKNOWN"; break;
    }

    // Print PID, state, and priority (assuming process name is available)
    cprintf("Name: %s, PID: %d, State: %s, Priority: %d\n", p->name, p->pid, state, p->priority);
  }
  release(&ptable.lock);
  return 0;
}
