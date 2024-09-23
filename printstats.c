#include "types.h"
#include "stat.h"
#include "user.h"
#include "sort.h"

#define ERROR 0.01
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
float sqrt(int x) {
    if (x == 0) return 0;
    if (x == 1) return 1;

    float result = (float)x;
    float left = 0;
    float right = x;

    while (right - left > ERROR) {
        result = (right + left) / 2;
        if (result * result == x) return result;
        if (result * result > x) {
            right = result;
        } else {
            left = result;
        }
    }
    return result;
}

// A program called “printstats” that takes a list of numbers and prints their average, standard deviation, median, min, and max.
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf(1, "Please provide at least one number\n");
        exit();
    }

    int i;
    int min = atoi(argv[1]);
    int max = atoi(argv[1]);
    int sum = 0;
    int arr[argc - 1];

    // Collect numbers and compute min, max, and sum
    for (i = 1; i < argc; i++) {
        arr[i - 1] = atoi(argv[i]);
        sum += atoi(argv[i]);
        if (min > atoi(argv[i])) {
            min = atoi(argv[i]);
        }
        if (max < atoi(argv[i])) {
            max = atoi(argv[i]);
        }
    }
    for(int i = 0; i < argc - 1; i++)
    {
        printf(1, "%d ", arr[i]);
    }
    printf(1, "\n");

    for(int i = 0; i < argc - 1; i++)
    {
        printf(1, "%d ", *argv[i+1]);
    }
    printf(1, "\n");

    float mean = (float)sum / (argc - 1);
    float difference_sum = 0;

    // Calculate variance
    for (int i = 1; i < argc; i++) {
        difference_sum += (atoi(argv[i]) - mean) * (atoi(argv[i]) - mean);
    }
    float variance = difference_sum / (argc - 1); // assuming population variance
    float standard_deviation = sqrt(variance);

    // Print results
    printf(1, "The mean is: %f\n", mean);
    printf(1, "The standard deviation is: %f\n", standard_deviation);
    printf(1, "The maximum is: %d\n", max);
    printf(1, "The minimum is: %d\n", min);  

    // Sort and calculate median
    sort(arr, argc - 1);
    printf(1, "Median: ");
    if ((argc - 1) % 2 == 0) {
        int median_index = (argc - 1) / 2;
        printf(1, "%d\n", (arr[median_index] + arr[median_index - 1]) / 2);
    } else {
        printf(1, "%d\n", arr[(argc - 1) / 2]);
    }
    printf(1,"%f\n",(int)mean);
    printf(1,"%d\n",(int)mean);
    printf(1,"%f\n",mean);
    printf(1,"%f\n",-1.5);
    exit();
}
