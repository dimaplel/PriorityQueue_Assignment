#include <queue>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include "Priority_Queue.h"
#include "HeapSort.h"

using namespace std;
template <typename T>
float testPriorityQueueSpeed(T&& priorityQueue)
{
    const int iters = 100000;
    clock_t timeStart = clock();
    for (int i = 0; i < iters; i++)
    {
        int insertDataAmount = rand() % 6 + 5;
        for (int j = 0; j < insertDataAmount; j++)
        {
            priorityQueue.push(Data());
        }
        priorityQueue.top();
        priorityQueue.pop();
    }
    clock_t timeEnd = clock();
    float time = (float(timeEnd - timeStart)) / CLOCKS_PER_SEC;
    return time;
}
bool testPriorityQueue()
{
    srand(time(NULL));
    const int iters = 20000;
    PriorityQueue myPriorQueue;

    priority_queue<Data> stlPriorQueue;
    bool isDataEqual = true;
    for (int i = 0; i < iters; i++)
    {
        int insertDataAmount = rand() % 6 + 5;
        for (int j = 0; j < insertDataAmount; j++)
        {
            Data randData = Data();
            myPriorQueue.push(randData);
            stlPriorQueue.push(randData);
        }
        if (myPriorQueue.top() != stlPriorQueue.top())
        {
            isDataEqual = false;
            cerr << "Comparing failed on iteration " << i << endl << endl;
            break;
        }
        int removeDataAmount = rand() % insertDataAmount;
        for (int j = 0; j < removeDataAmount; j++)
        {
            myPriorQueue.pop();
            stlPriorQueue.pop();
        }
    }
    int myQueueSize = myPriorQueue.size();
    int stlQueueSize = stlPriorQueue.size();
    float stlTime =
            testPriorityQueueSpeed<priority_queue<Data>>(priority_queue<Data>());
    float myTime = testPriorityQueueSpeed<PriorityQueue>(PriorityQueue());
    cout << "My PriorityQueue:" << endl;
    cout << "Time: " << myTime << ", size: " << myQueueSize << endl;
    cout << "STL priority_queue:" << endl;
    cout << "Time: " << stlTime << ", size: " << stlQueueSize << endl << endl;
    if (isDataEqual && myQueueSize == stlQueueSize)
    {
        cout << "The lab is completed" << endl << endl;
        return true;
    }
    cerr << ":(" << endl << endl;
    return false;
}

void testHeapSorting()
{
    srand(time(NULL));
    const size_t iters = 500000;
    vector<Data> array;
    vector<Data> stlCopy;

    for(int i = 0; i < iters; i++)
    {
        Data randData = Data();
        array.push_back(randData);
        stlCopy.push_back(randData);
    }

    clock_t stlStart = clock();
    sort(stlCopy.begin(), stlCopy.end());
    clock_t stlEnd = clock();
    cout << "Stl sort done sorting after: " << ((double)(stlEnd - stlStart)) / CLOCKS_PER_SEC << " seconds\n";
    clock_t heapStart = clock();
    heapSort(array);
    clock_t heapEnd = clock();
    cout << "Heap sort done sorting after: " << ((double)(heapEnd - heapStart)) / CLOCKS_PER_SEC << " seconds\n\n";


    bool isEqual = true;
    for(int i = 1; i < iters; i++)
    {
        if(array[i] != stlCopy[i] || array[i].urgency < array[i-1].urgency)
        {
            std::cerr << "Stopped checking equality and sorting at iter: " << i << std::endl;
            isEqual = false;
            break;
        }
    }

    if(isEqual)
        std::cout << "The additional task is completed!\n";
    else
        std::cerr << "Something went wrong :(\n";

}

int main()
{
    testPriorityQueue();
    testHeapSorting();
    return 0;
}