#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // create temporary arrays
    int leftArray[n1], rightArray[n2];

    // copy data to temporary arrays leftArray[] and rightArray[]
    for (i = 0; i < n1; i++)
    {
        leftArray[i] = arr[left + i];
    }

    for (j = 0; j < n2; j++)
    {
        rightArray[j] = arr[mid + 1 + j];
    }

    // merge temporary arrays back into arr[left...right]
    i = 0;    // initial index of first subarray
    j = 0;    // initital index of second subarray
    k = left; // initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (leftArray[i] <= rightArray[j])
        {
            arr[k] = leftArray[i];
            i++;
        }
        else
        {
            arr[k] = rightArray[j];
            j++;
        }
        k++;
    }

    // copy remaining elements of leftArray[], if there are any
    while (i < n1)
    {
        arr[k] = leftArray[i];
        i++;
        k++;
    }

    // copy remaining elements of rightArray[], if there are any
    while (j < n2)
    {
        arr[k] = rightArray[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {

        // sam as (left + right) / 2 but avoids overflow
        // for large left and right
        int mid = left + (right - left) / 2;

        // sort first and second halves of arr
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // merge the two sorted halves
        merge(arr, left, mid, right);
    }
}