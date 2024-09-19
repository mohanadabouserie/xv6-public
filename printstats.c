#include "types.h"
#include "stat.h"
#include "user.h"

// A program called “printstats” that takes a list of numbers and prints their average, standard deviation, median, min and max.
int
main(int argc, char *argv[])
{
  int i;
  int min = atoi(argv[1]);
  int max = atoi(argv[1]);
  int sum = 0;
  for(i = 1; i < argc; i++){
sum += atoi(argv[i]);
if(min>atoi(argv[i])){
  min = atoi(argv[i]);
}
if(max < atoi(argv[i])){
  max = atoi(argv[i]);
}
  }
    
  int mean = sum/(argc-1);
  printf(1, "%s%d\n%s%d\n%s%d\n", "The mean is: ",mean, "The maximum is: ", max,"The minimum is: ", min);   
  exit();
}

