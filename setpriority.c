// setpriority.c
#include "user.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf(2, "Usage: setpriority <pid> <priority>\n");
    exit();
  }

  int pid = atoi(argv[1]);
  int priority = atoi(argv[2]);

  int old_priority = setpriority(pid, priority);
 
    printf(1, "Priority of process %d changed from %d to %d\n", pid, old_priority, priority);
  

  exit();
}

