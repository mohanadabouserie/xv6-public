#include "types.h"
#include "stat.h"
#include "user.h"
#define error 4
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
  if(neg && !sgn) // to handle decimal part in floating points
    buf[i++] = '-';

  while(--i >= 0)
    putc(fd, buf[i]);
}

static void
printfloat(int fd, double xx, int base, int sgn)
{
    int integer_part;
    int decimal_part;
    int exponent = 1;

    integer_part = (int)xx;
    printint(fd,integer_part,base,sgn);
    putc(fd,'.');
    for(int i=0;i<error;i++)
      exponent*=10;
    decimal_part = (int)((xx - (double)integer_part)*(double)exponent);  
    printint(fd,decimal_part,base,sgn);
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
        double *fp = (double *)ap;
        printfloat(fd,*fp, 10, 1);
        ap+=2;
        
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
