#include <iostream>
#include <vector>


template <typename T>
class HashNode{
    HashNode* next;
    T data;
};

template <typename T>
class HashTable{
public:
    HashTable(size_t size){

    }
    ~HashTable();

    bool Add(const T &key);
    bool Delete(const T&key);

private:
    std::vector<TableHashNode> table;
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}