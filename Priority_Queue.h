#ifndef PRIORITYQ_BINARYHEAP_PRIORITY_QUEUE_H
#define PRIORITYQ_BINARYHEAP_PRIORITY_QUEUE_H

#include <vector>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>

using std::vector;
using std::size_t;

enum Category
{
    CIVIL, MILITARY
};

Category getRandCat(int rand_num)
{
    if(rand_num == 0)
        return CIVIL;
    return MILITARY;
}
struct Data
{
    float quality;
    float urgency;
    Category category;
    Data()
    {
        quality = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 100);
        urgency = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 10);
        category = getRandCat(rand() % 2);
    }
    bool operator==(const Data& secondData) const
    {
        return (category == secondData.category && urgency == secondData.urgency && quality == secondData.quality);
    }
    bool operator<(const Data& secondData) const
    {
        if(urgency != secondData.urgency)
        {
            return urgency < secondData.urgency;
        }
        if(category != secondData.category)
        {
            return category < secondData.category;
        }
        if(quality != secondData.quality)
        {
            return quality < secondData.quality;
        }
        return false;
    }

    bool operator<=(const Data& secondData) const
    {
        return (*this < secondData || *this == secondData);
    }

    bool operator!=(const Data& secondData) const
    {
        return !(*this==secondData);
    }
};


struct PriorityQueue
{
    vector<Data> buckets;
    size_t queue_size = 0;

    PriorityQueue() = default;
    ~PriorityQueue() = default;

    static void swap(Data& fNode, Data& sNode)
    {
        Data copy = fNode;
        fNode = sNode;
        sNode = copy;
    }

    static size_t getParent(size_t node){return (node - 1) / 2;}
    static size_t getLeftChild(size_t parent) {return 2 * parent + 1;}
    static size_t getRightChild(size_t parent) {return 2 * parent + 2;}
    const Data& top(){return buckets[0];}
    size_t size() const {return queue_size;}
    bool empty() const {return queue_size==0;}
    static bool isRoot(size_t index) {return index == 0;}
    bool isLeaf(size_t index) const {return getLeftChild(index) >= queue_size;}
    size_t height() const{return roundf(log2f(static_cast<float>(queue_size)));}

    void siftUp(size_t node)
    {
        if(isRoot(node))
        {
            return;
        }
        size_t parentNode = getParent(node);

        while(buckets[parentNode] < buckets[node])
        {
            swap(buckets[node], buckets[parentNode]);
            if(isRoot(node) || isRoot(parentNode))
                return;
            node = parentNode;
            parentNode = getParent(node);
        }
    }

    size_t maxChildNode(size_t leftChild, size_t rightChild)
    {
        return (buckets[leftChild] <= buckets[rightChild])? rightChild : leftChild;
    }

    void siftDown(size_t node)
    {
        if(isLeaf(node))
        {
            return;
        }

        size_t maxChildIndex = getLeftChild(node);
        if(getRightChild(node) < queue_size)
        {
            maxChildIndex = maxChildNode(maxChildIndex, getRightChild(node));
        }

        while(buckets[node] < buckets[maxChildIndex])
        {
            swap(buckets[maxChildIndex], buckets[node]);

            if(isLeaf(node) || isLeaf(maxChildIndex))
                return;

            node = maxChildIndex;
            maxChildIndex = getLeftChild(node);
            if(getRightChild(node) < queue_size)
            {
                maxChildIndex = maxChildNode(maxChildIndex, getRightChild(node));
            }
        }
    }

    void pop()
    {
        if(empty())
        {
            return;
        }

        swap(buckets[0], buckets[queue_size - 1]);
        queue_size--;
        buckets.erase(buckets.end() - 1);

        siftDown(0);
    }

    void push(Data priority)
    {
        buckets.push_back(priority);
        queue_size++;

        siftUp(queue_size - 1);
    }

};
#endif /*PRIORITYQ_BINARYHEAP_PRIORITY_QUEUE_H*/