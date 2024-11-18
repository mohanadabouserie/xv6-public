#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


#define MAX 1000
#define MIN 0
#define DEFAULT (MAX+MIN)/2
void busy_work(int iterations) {

    int i, j;
    for(i = 0; i < iterations; i++) {
        int x = 0;
        for(j = 0; j < 1000000; j++) {
            x = x + j%10;
        }
        printf(1, "Process %d finished iteration %d with result %d and priority %d at time %d\n", getpid(), i,x, getpriority(getpid()),gettime());
    }
    // This is a sample p-table
    printf(1,"This is the process table after finishing process %d: \n", getpid());
    printf(1,"------------------------------------------------------------------\n");
    printptable();
    printf(1,"------------------------------------------------------------------\n");
}

int main(int argc, char *argv[]) {
    printptable();
    // Argument validation
    if(argc != 5){
      printf(2,"Note: testscheduler takes <N-PROC> <sign> <factor> <iterations>, for sign 1->positive, 0->negative\n");
      exit();
    }  
    int n = atoi(argv[1]); 
    int sign = atoi(argv[2]);  
    int factor = atoi(argv[3]);
    int iterations = atoi(argv[4]);
    if (n <= 0) {
        printf(2, "Error: <N-PROC> must be a positive integer.\n");
        exit();
    }

    if (sign != 0 && sign != 1) {
        printf(2, "Error: <sign> must be either 1 (positive) or 0 (negative).\n");
        exit();
    }
    
    if(factor > (DEFAULT-MIN) / n){
        printf(2, "You should select a relevant factor that is smaller than <DEFAULT-1>/<N_PROC> where <DEFAULT> is: %d\n", DEFAULT);
        exit();
    } // factor can't be negative as xv6 does not accept negative numbers

    if(iterations < 1){
        printf(2, "You should select a relevant iteration integer number that is greater than 0");
        exit();
    } 

    int i;
    
    printf(1, "Testing priority decay scheduler in xv6...\n");
    // calculating the factor each next children will have priority based on
    if(!sign) {sign = -1;}
    
    int priority = DEFAULT;
    for(i = 0; i < n; i++) {
        int pid = fork();
        if(pid == 0) {
            priority = priority + sign * factor * i;
            setpriority(getpid(),priority); // Note that sometimes the print of the new child will be before as it has higher priority
            printf(1,"This is process with pid: %d and priority %d\n",getpid(), getpriority(getpid()));
            busy_work(iterations); 
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
