#include <iostream>
#include <array>
#include <vector>
#include <assert.h>

const int MIN_SIZE = 10;
const int MEM_INCREASE = 2;

template<typename T>
class Array;


template<typename T>
class Heap {
public:
    Heap() = default;

    explicit Heap(const Array<T> &_arr);

    ~Heap() = default;

    bool isEmpty();

    void insert(const T &element);

    int getSize();

    T extract_max();

    const T &peek_max();


private:
    Array<T> array;

    void siftUp(int i);

    void siftDown(int index);
};

template<typename T>
void Heap<T>::siftDown(int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    int largest = index;
    if (left < array.getSize() && array[left] > array[largest]) {
        largest = left;
    }
    if (right < array.getSize() && array[right] > array[largest]) {
        largest = right;
    }
    if (largest != index) {
        std::swap(array[largest], array[index]);
        siftDown(largest);
    }
}

template<typename T>
void Heap<T>::siftUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (array[index] <= array[parent])
            return;
        std::swap(array[index], array[parent]);
        index = parent;
    }
}

template<typename T>
Heap<T>::Heap(const Array<T> &_arr): array(_arr) {
    for (int i = array.getSize() / 2 - 1; i >= 0; --i) {
        siftDown(i);
    }
}

template<typename T>
bool Heap<T>::isEmpty() {
    return array.isEmpty();
}

template<typename T>
void Heap<T>::insert(const T &element) {
    array.add(element);
    siftUp(array.getSize() - 1);
}

template<typename T>
T Heap<T>::extract_max() {
    T tmp = array[0];
    array[0] = array[array.getSize() - 1];
    array[array.getSize()-1]=tmp;
    array.erase(array.getSize() - 1);
    if (!array.isEmpty()) {
        siftDown(0);
    }
    return tmp;
}

template<typename T>
const T &Heap<T>::peek_max() {
    return array[0];
}

template<typename T>
int Heap<T>::getSize() {
    return array.getSize();
}


/*------------------------ARRAY---------------------------*/
template<typename T>
class Array {
public:

    Array();

//    Array(const T &);
//    void operator=(const T&);

    ~Array();

    void add(const T &);

    void erase(int);

    void remove(const T &);

    int getSize() const;

    T &at(int);

    bool isEmpty();

    T &operator[](int);

private:
    T *buffer;
    size_t capacity;
    int size;

    void resize();
};

template<typename T>
Array<T>::Array() {
    capacity = MIN_SIZE;
    size = 0;
    buffer = new T[capacity];
}

template<typename T>
Array<T>::~Array() {
    delete[] buffer;
}

template<typename T>
void Array<T>::add(const T &elem) {
    resize();

    buffer[size]= elem;
    size++;
}

template<typename T>
void Array<T>::resize() {
    if (size + 1 > capacity) {
        capacity *= MEM_INCREASE;
        T *tmp = new T[capacity];
        if (size) {
            for (int i = 0; i < size; i++) {
                tmp[i] = buffer[i];
            }
        }
        delete[] buffer;
        buffer = tmp;
    }
    if (size <= capacity / MEM_INCREASE && capacity / MEM_INCREASE >= MIN_SIZE) {
        capacity /= MEM_INCREASE;
        T *tmp = new T[capacity];
        if (size) {
            for (int i = 0; i < size; ++i) {
                tmp[i] = buffer[i];
            }
        }
        delete[] buffer;
        buffer = tmp;
    }
}

template<typename T>
void Array<T>::erase(int index) {
    assert (!isEmpty() || index < size);
    T *tmp = buffer + index;
    for (int i = index; i < size - 1; i++) {
        buffer[i] = buffer[i + 1];
    }
    size--;
}

template<typename T>
void Array<T>::remove(const T &elem) {
    assert(!isEmpty());
    int index = 0;
    while (buffer[index] != elem) {
        index++;
    }
    T *tmp = buffer[index];
    for (int i = index; i < size - 1; i++) {
        buffer[i] = buffer[i + 1];
    }
}

//TODO  RVO Optimization!!!

template<typename T>
T &Array<T>::at(int index) {
    assert(!isEmpty() && index < size);
    return buffer[index];
}

template<typename T>
T &Array<T>::operator[](int index) {
    assert(!isEmpty() && index < size);
    return buffer[index];
}

template<typename T>
bool Array<T>::isEmpty() {
    return !size;
}

template<typename T>

int Array<T>::getSize() const {
    return size;
}

struct Elem {
    int index;
    int number;

    Elem(int index=0, int number=0) : index(index), number(number) {}
};

bool operator>(const Elem &lhs, const Elem &rhs) {
    return lhs.number > rhs.number;
}

bool operator<=(const Elem &lhs, const Elem &rhs) {
    return !(lhs > rhs);
}

int main() {
    Heap<Elem> heap;
    int n, k;

    std::cin >> n;
    int *array=new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> array[i];
    }
    std::cin >> k;

    if(n==0 || k==0){
        delete [] array;
        return 0;
    }

    for (int i = 0; i < n; i++) {
        int number;
        heap.insert(Elem(i,array[i]));
        if(heap.getSize()>=k){
            while(heap.peek_max().index<i-k+1){
                heap.extract_max();
            }
            std::cout<<heap.peek_max().number<<" ";
        }
    }

    delete []array;
    return 0;
}
