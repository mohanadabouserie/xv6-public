#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]) {
  int pid;
  int k, n;
  int x, z;

  if(argc < 2)
	n = 1; // default
  else
	n = atoi(argv[1]); // convert argument 1 to int
  if (n < 0 ||n > 20) // number of child processes
	n = 2;
  x = 0;
  pid = 0;

  for ( k = 0; k < n; k++ ) {
    pid = fork ();
    if (pid < 0) {
      printf(1, "%d failed in fork!\n", getpid());
    } 
    else if (pid > 0) {
      // parent
      printf(1, "Parent %d creating child %d\n",getpid(), pid);
      wait();
      }
    else {
	    printf(1,"Child %d created\n",getpid());
      printptable();
	    for(z = 0; z < 400000; z+=1)
	      x = x + 3.14*89.64; // consume CPU time
      break;
    }
  }
  exit();
}