#ifndef PRIORITYQ_BINARYHEAP_HEAPSORT_H
#define PRIORITYQ_BINARYHEAP_HEAPSORT_H

#include <vector>
#include <iostream>
#include <algorithm>
#include "Priority_Queue.h"

using std::vector;

void heapify(vector<Data>& arr, size_t size, int iter)
{
    size_t leftChild = 2 * iter + 1;
    size_t rightChild = 2 * iter + 2;
    size_t max = iter;

    if(leftChild < size && arr[max] < arr[leftChild])
        max = leftChild;
    if(rightChild < size && arr[max] < arr[rightChild])
        max = rightChild;

    if(max != iter)
    {
        PriorityQueue::swap(arr[max], arr[iter]);
        heapify(arr, size, max);
    }
}

void heapSort(vector<Data>& arr)
{
    size_t size = arr.size();
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(arr, size, i);

    for (int i = size - 1; i > 0; i--)
    {
        PriorityQueue::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void printArray(vector<Data> arr, size_t n)
{
    for (int i = 0; i < n; ++i)
    {
        if(i != n-1 && arr[i].urgency > arr[i+1].urgency)
        {
            std::cout << "Error in sorting!\n";
        }
        std::cout << arr[i].urgency << " ";
    }
    std::cout << "\n";
}


#endif //PRIORITYQ_BINARYHEAP_HEAPSORT_H