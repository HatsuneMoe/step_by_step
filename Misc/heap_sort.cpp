#include <vector>
#include <iostream>

using std::vector;

void swap(int &a, int &b)
{
    a ^= b, b ^= a, a ^= b;
}

int heapify(vector<int> &heap, int begin, int end)
{
    int lchild = 2 * begin + 1;
    int largest = begin;
    // lchild <= end;
    if (lchild <= end && heap[lchild] > heap[largest]){
        largest = lchild;
    }
    if (lchild+1 <= end && heap[lchild+1] > heap[largest]){
        largest = lchild+1;
    }

    if (largest != begin){
        swap(heap[begin], heap[largest]);
        heapify(heap, largest, end);
    }

    return 0;
}

int build_heap(vector<int> &heap, int end)
{
    for (int i=heap.size()/2; i>=0; --i)
        heapify(heap, i, end);
    return 0;
}

int heap_sort(vector<int> &heap)
{
    build_heap(heap, heap.size()-1);
    for (int i=heap.size()-1; i>0;)
    {
        swap(heap[0], heap[i]);
        build_heap(heap, --i);
    }
    return 0;
}

int main()
{
    vector<int> heap = {1};
    heap_sort(heap);
    for (auto &i: heap)
        std::cout << i << " " ;
    return 0;
}