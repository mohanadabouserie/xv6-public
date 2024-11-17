#include "user.h"
#include "types.h"
#include "stat.h"
#include "fcntl.h"

int main(void)
{
    int time = gettime();
    printf(1, "Current time: %d seconds since epoch\n", time);
    exit();
}
