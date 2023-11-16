#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"


extern int schedmod(int mode);

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

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
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
    if(proc->killed){
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


int sys_nice(void) 
{
  int n;
  if(argint(0, &n) < 0) 
      return -1;

  if(n < 0)
      return -1; 
  else if(n > 39)
  {
      proc->nice = 39;
      proc->tickets= 10;
  }
  else 
  {
      proc->nice = n;
      if(n==0)
      {
        proc->tickets = 400;
      }
      else
      {
      proc->tickets = 400 - (10*n);
      }
  }
  //assign_tickets(proc);
  return proc->nice;
}



int sys_schedmod(void) {
    int mode;

    if (argint(0, &mode) < 0) {
        return -1;
    }

    if (mode != 0 && mode != 1) {
        mode = 0; // If the mode is not 0 or 1, reset it to 0.
    }
    
    return schedmod(mode); // No need to store the return in ret_mode, just return it directly.
}



int sys_rettickets(void){
  return proc->tickets;
}

int sys_retcpucount(void){
  return proc->count;
}

