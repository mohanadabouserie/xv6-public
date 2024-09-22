#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf(1, "Please provide at least one number\n");
        exit();
    }
    int arr[argc - 1];
    for(int i = 1; i < argc; i++)
    {
        arr[i - 1] = atoi(argv[i]);
    }
    for(int i = 0; i < argc - 2; i++)
    {
        for(int j = 0; j < argc - 2 - i; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    for(int i = 0; i < argc - 1; i++)
    {
        printf(1, "%d ", arr[i]);
    }
    printf(1, "\n");
    exit();
}