#include "types.h"
#include "user.h"
#include "syscall.h"

// Main function for testing the syscall
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf(2, "Usage: truncate <filename> <size>\n");
        exit();
    }

    char *filename = argv[1];
    int new_size = atoi(argv[2]);

    if (truncate(filename, new_size) < 0) {
        printf(2, "truncate failed \n");
        exit();
    }

    printf(1,"Truncated %s to %d bytes\n", filename, new_size);
    exit();
}
