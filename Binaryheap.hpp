#ifndef BINARYHEAP_HPP
#define BINARYHEAP_HPP
#include <vector>
#include <string>
#include "HashMap.hpp"

class BinaryHeap {
private:
    struct HeapNode {
        std::string file_name;
        int comp;

        HeapNode(const std::string& fn, const int& c); 
    };
    int size;
    std::vector<HeapNode> heap;
    HashMap index_map; 
public:    
    BinaryHeap();
    void heapify_up(int index);
    void heapify_down(int index);
    void insert(const std::string& file_name, const int& c);
    void pop();
    void swap(int i, int j);
    void update(const std::string& file_name, const int& new_c);
    std::pair<std::string, int> get_max();
    int get_file_count() { return size; }
};

#endif