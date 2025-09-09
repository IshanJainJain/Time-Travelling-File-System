#include "HashMap.hpp"

Node::Node(const std::string k, const long long v)
{
    this->key = k;
    this->value = v;
    this->next = nullptr;
}

unsigned long long HashMap::hash(const std::string &key)
{
    unsigned long long h = 5381;
        for (char c : key) {
            h = ((h << 5) + h);
            h += (unsigned char)c;
        }
        return h;
}

size_t HashMap::getIndex(const std::string &key)
{
    return hash(key) & (capacity - 1);
}

void HashMap::rehash()
{
    size_t oldcap = capacity;
    capacity *= 2;
    std::vector<Node*> newtable(capacity, nullptr);
    
    for (size_t i=0; i<oldcap; i++) {
        Node* curr = table[i];

        while (curr) {
            Node* tempnext = curr->next;
            size_t newindex = getIndex(curr->key);

            curr->next = newtable[newindex];
            newtable[newindex] = curr;

            curr = tempnext;
        }
    }

    table.swap(newtable);
}

HashMap::HashMap()
{
    capacity = 1;
    table.resize(capacity, nullptr);
    size = 0;
}

void HashMap::insert(const std::string &key, const long long &value)
{
    if ((double)size / capacity > thresh) {
        rehash();
    }

    size_t ind = getIndex(key);
    Node* curr = table[ind];

    while (curr) {
        if (curr->key == key) {
            curr->value = value;
            return;
        }
        curr = curr->next;
    }

    Node* newnode = new Node(key, value);
    newnode->next = table[ind];
    table[ind] = newnode;
    return;

}

long long HashMap::get(const std::string &key)
{
    size_t ind = getIndex(key);
    Node* curr = table[ind];

    while (curr) {
        if (curr->key == key) {
            return curr->value;
        }
        curr = curr->next;
    }

    throw std::out_of_range("Key not found: " + key);
}

Node1::Node1(const std::string k, Tree *v)
{
    this->key = k;
    this->value = v;
    this->next = nullptr;
}

unsigned long long HashMap1::hash(const std::string &key)
{
    unsigned long long h = 5381;
        for (char c : key) {
            h = ((h << 5) + h);
            h += (unsigned char)c;
        }
        return h;
}

size_t HashMap1::getIndex(const std::string &key)
{
    return hash(key) & (capacity - 1);
}

void HashMap1::rehash()
{
    size_t oldcap = capacity;
    capacity *= 2;
    std::vector<Node1*> newtable(capacity, nullptr);
    
    for (size_t i=0; i<oldcap; i++) {
        Node1* curr = table[i];

        while (curr) {
            Node1* tempnext = curr->next;
            size_t newindex = getIndex(curr->key);

            curr->next = newtable[newindex];
            newtable[newindex] = curr;

            curr = tempnext;
        }
    }

    table.swap(newtable);
}

HashMap1::HashMap1()
{
    capacity = 1;
    table.resize(capacity, nullptr);
    size = 0;
}

void HashMap1::insert(const std::string &key, Tree *value)
{
    if ((double)size / capacity > thresh) {
        rehash();
    }

    size_t ind = getIndex(key);
    Node1* curr = table[ind];

    while (curr) {
        if (curr->key == key) {
            curr->value = value;
            return;
        }
        curr = curr->next;
    }

    Node1* newnode = new Node1(key, value);
    newnode->next = table[ind];
    table[ind] = newnode;
    return;

}

Tree* HashMap1::get(const std::string &key)
{
    size_t ind = getIndex(key);
    Node1* curr = table[ind];

    while (curr) {
        if (curr->key == key) {
            return curr->value;
        }
        curr = curr->next;
    }

    throw std::out_of_range("Key not found: " + key);
}

