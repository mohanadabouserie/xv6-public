#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


#define MAX 1000
#define MIN 0
#define DEFAULT (MAX+MIN)/2
void busy_work() {

    int i, j;
    for(i = 0; i < 10; i++) {
        int x = 0;
        for(j = 0; j < 1000000; j++) {
            x = x + j%10;
        }
        printf(1, "Process %d finished iteration %d with result %d and priority %d at time %d\n", getpid(), i,x, getpriority(getpid()),gettime());
    }
}

int main(int argc, char *argv[]) {
    // Argument validation
    if(argc != 4){
      printf(2,"Note: testscheduler takes <N-PROC> <sign> <factor>, for sign 1->positive, 0->negative");
    }  
    int n = atoi(argv[1]); 
    int sign = atoi(argv[2]);  
    int factor = atoi(argv[3]);

    if (n <= 0) {
        printf(2, "Error: <N-PROC> must be a positive integer.\n");
        exit();
    }

    if (sign != 0 && sign != 1) {
        printf(2, "Error: <sign> must be either 1 (positive) or 0 (negative).\n");
        exit();
    }
    
    if(factor > (DEFAULT-MIN) / n){
        printf(2, "You should select a relevant factor that is smaller than <DEFAULT-1>/<N_PROC>");
    } // factor can't be negative as xv6 does not accept negative numbers

    int i;
    
    printf(1, "Testing priority decay scheduler in xv6...\n");
    // calculating the factor each next children will have priority based on
    if(!sign) sign = -1;
    
    int priority = DEFAULT;
    for(i = 0; i < n; i++) {
        int pid = fork();
        if(pid == 0) {
            priority = priority + factor*i;
            setpriority(getpid(),priority);
            printf(1,"This is process with pid: %d and priority %d\n",getpid(), getpriority(getpid()));
            busy_work(); 
            exit(); 
        }
        
    }
    
    for(i = 0; i < n; i++) {
      // We loop so that it waits for all of its n-children
        wait();
    }
    
    printf(1, "Priority decay test completed.\n");
    exit();
}
