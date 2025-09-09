#include "Binaryheap.hpp"

BinaryHeap::HeapNode::HeapNode(const std::string &fn, const int &c)
{
    this->file_name = fn;
    this->comp = c;
}

BinaryHeap::BinaryHeap()
{
    size = 0;
}

void BinaryHeap::heapify_up(int index)
{
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index].comp <= heap[parent].comp) {
            break;
        }
        swap(index, parent);
        index = parent;
    }
}

void BinaryHeap::heapify_down(int index)
{
    int left, right, biggest;
    while (true) {
        left = 2 * index + 1;
        right = 2 * index + 2;
        biggest = index;

        if (left < size && heap[left].comp > heap[biggest].comp) {
            biggest = left;
        }
        if (right < size && heap[right].comp > heap[biggest].comp) {
            biggest = right;
        }
        if (biggest == index) {
            break;
        }
        swap(index, biggest);
        index = biggest;
    }
}

void BinaryHeap::insert(const std::string &file_name, const int &c)
{
    HeapNode* newNode = new HeapNode(file_name, c);
    heap.push_back(*newNode);
    size++;
    index_map.insert(file_name, size - 1);
    heapify_up(size - 1);
}

void BinaryHeap::pop()
{
    if (size == 0) return;

    swap(0, size - 1);
    heap.pop_back();
    size--;
    heapify_down(0);
}

void BinaryHeap::swap(int i, int j)
{
    std::swap(heap[i], heap[j]);
    index_map.insert(heap[i].file_name, i);
    index_map.insert(heap[j].file_name, j);
}

void BinaryHeap::update(const std::string &file_name, const int &new_c)
{
    size_t index = index_map.get(file_name);
    if (index >= size) return;

    int old_c = heap[index].comp;
    heap[index].comp = new_c;

    if (new_c > old_c) {
        heapify_up(index);
    } else {
        heapify_down(index);
    }
}

std::pair<std::string, int> BinaryHeap::get_max()
{
    if (size == 0) return {"", -1};
    return {heap[0].file_name, heap[0].comp};
}
