#ifndef HASHMAP_HPP
#define HASHMAP_HPP
#include "TreeNode.hpp"
#include <string>
#include <vector>
#include <stdexcept>

class Node {
public:
    std::string key;
    long long value;
    Node* next;

public:
    Node(const std::string k, const long long v);
};

class HashMap {
private:
    std::vector<Node*> table;
    size_t size;
    size_t capacity;
    const double thresh = 0.7;

public:
    unsigned long long hash(const std::string& key);
    size_t getIndex(const std::string& key);
    void rehash();
    HashMap();
    void insert(const std::string& key, const long long& value);
    long long get(const std::string& key);
};

class Node1 {
public:
    std::string key;
    Tree* value;
    Node1* next;
public:
    Node1(const std::string k, Tree* v);
};

class HashMap1 {
private:
    std::vector<Node1*> table;
    size_t size;
    size_t capacity;
    const double thresh = 0.7;

public:
    unsigned long long hash(const std::string& key);
    size_t getIndex(const std::string& key);
    void rehash();
    HashMap1();
    void insert(const std::string& key, Tree* value);
    Tree* get(const std::string& key);
};
#endif