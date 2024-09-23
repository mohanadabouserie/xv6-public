#include "types.h"
#include "stat.h"
#include "user.h"
#define error 1
static void
putc(int fd, char c)
{
  write(fd, &c, 1);
}

static void
printint(int fd, int xx, int base, int sgn)
{
  static char digits[] = "0123456789ABCDEF";
  char buf[16];
  int i, neg;
  uint x;

  neg = 0;
  if(sgn && xx < 0){
    neg = 1;
    x = -xx;
  } else {
    x = xx;
  }

  i = 0;
  do{
    buf[i++] = digits[x % base];
  }while((x /= base) != 0);
  if(neg)
    buf[i++] = '-';

  while(--i >= 0)
    putc(fd, buf[i]);
}

static void
printfloat(int fd, double xx, int base, int sgn)
{
  
  double x;
printint(fd,(int)xx,base,sgn);
putc(fd,'.');
  if(sgn && xx < 0){
    x = -xx;
  } else {
    x = xx;
  }

    
  int value = 1;
  printf(1,"\n Before for loop: %d\n",(int)x);
  for(int j=0;j<error;j++){
    // printf(1,"Enter");
x = x * 10;
value = value * 10;
  }
  printf(1,"\n test: %d\n",(int)x);
  int float_part = (int)x%value;
  printf(1,"floating part: %d\n",float_part);
  printint(fd,float_part,base,0);  
  
}

// Print to the given fd. Only understands %d, %x, %p, %s.
void
printf(int fd, const char *fmt, ...)
{
  char *s;
  int c, i, state;
  uint *ap;

  state = 0;
  ap = (uint*)(void*)&fmt + 1;
  for(i = 0; fmt[i]; i++){
    c = fmt[i] & 0xff;
    if(state == 0){
      if(c == '%'){
        state = '%';
      } else {
        putc(fd, c);
      }
    } else if(state == '%'){
      if(c == 'd'){
        printint(fd, *ap, 10, 1);
        ap++;
      } else if(c == 'f'){
        printfloat(fd, (double)*ap, 10, 1);
        ap++;
        
      } else if(c == 'x' || c == 'p'){
        printint(fd, *ap, 16, 0);
        ap++;
      } else if(c == 's'){
        s = (char*)*ap;
        ap++;
        if(s == 0)
          s = "(null)";
        while(*s != 0){
          putc(fd, *s);
          s++;
        }
      } else if(c == 'c'){
        putc(fd, *ap);
        ap++;
      } else if(c == '%'){
        putc(fd, c);
      } else {
        // Unknown % sequence.  Print it to draw attention.
        putc(fd, '%');
        putc(fd, c);
      }
      state = 0;
    }
  }
}
