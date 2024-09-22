#include "types.h"
#include "stat.h"
#include "user.h"
#define error 0.01
float sqrt(int x){
  if(x==0)return 0;
  if(x==1) return 1;
  float result = (float)x;
  float left = 0;
  float right = x;
  while(right-left>error){
    result = (right+left)/2;
    if(result*result == x) return result;
    if(result*result > x) right = right-(right-left)/2;
    if(result*result < x) left = left+(right-left)/2; 
    printf(1,"left value is: %d\nRight value is: %d\n",(int)left,(int)right);
  }
  printf(1,"The final result is: %d\n: ", (int)result);
  return result;
}
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
    
  float mean = sum/(argc-1);
  float difference_sum = 0;
  for(int i=1;i<argc;i++){
    difference_sum+= atoi(argv[i]);
  }
  float variance = difference_sum / (argc-1); // assuming population variance
  float standard_deviation = sqrt(variance);
  // int test = (int) sqrt(mean);
  printf(1, "%s%d\n%s%d\n%s%d\n%s%d\n", "The mean is: ",(int)mean, "The standard deviation is: ",(int)standard_deviation,"The maximum is: ", max,"The minimum is: ", min);   
  exit();
}

