#include "types.h"
#include "stat.h"
#include "user.h"
void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
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
    sort(arr,argc-1);
    for(int i = 0; i < argc - 1; i++)
    {
        printf(1, "%d ", arr[i]);
    }
    printf(1, "\n");
    exit();
}