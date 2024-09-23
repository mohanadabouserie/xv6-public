#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char* argv[]) {

    if (argc < 3)
    {
        printf(1, "Please file name and string to print\n");
        exit();
    }

    char* filename = argv[1];
    char* string = argv[2];

    int openfile = open(filename, O_CREATE | O_WRONLY);

    write(openfile, string, strlen(string));

    close(openfile);

    exit();
}