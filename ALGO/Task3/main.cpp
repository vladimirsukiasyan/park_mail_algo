/*
 * Сукиасян Владимир, АПО-13
 *
Реализовать очередь с динамическим зацикленным буфером.

Обрабатывать команды push back и pop front.

Формат ввода
В первой строке количество команд n. n ≤ 1000000.

Каждая команда задаётся как 2 целых числа: a b.

a = 2 - pop front
a = 3 - push back

Если дана команда pop front, то число b - ожидаемое значение.
Если команда pop front вызвана для пустой структуры данных, то ожидается “-1”.

Формат вывода
Требуется напечатать YES - если все ожидаемые значения совпали.
Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
*/
#include <iostream>

#define MIN_SIZE 10
#define MEM_INCREASE 2

template<typename T>
class Queue {

public:
    Queue();;

    ~Queue();

    void enqueue(const T &);

    T dequeue();

    bool isEmpty();

private:
    size_t head;
    size_t tail;
    struct buffer {
        T *buffer;
        size_t capacity;
        size_t size;
    } buf;

    void resize();
};


template<typename T>
Queue<T>::Queue(): head(0), tail(0) {
    buf.buffer = new T[MIN_SIZE];
    buf.capacity = MIN_SIZE;
    buf.size = 0;
}

template<typename T>
Queue<T>::~Queue() {
    delete[] buf.buffer;
}

template<typename T>
bool Queue<T>::isEmpty() {
    return !buf.size;
}

template<typename T>
void Queue<T>::enqueue(const T &elem) {
    resize();

    buf.buffer[tail] = elem;
    buf.size++;
    tail = (tail + 1) % buf.capacity;

}

template<typename T>
T Queue<T>::dequeue() {
    if (isEmpty()) {
        return -1;
    }
    T tmp = buf.buffer[head];

    //For supporting primitive types and classes simultaneously, we should check type of T via is_fundamental()
    //So we do delete[] for classes or mark primitive type blocks by -1;
    if constexpr (!std::is_fundamental<T>::value) {
        delete buf.buffer[head];
    }

    head = (head + 1) % buf.capacity;
    buf.size--;
    return tmp;
}

template<typename T>
void Queue<T>::resize() {
    if (buf.size + 1 > buf.capacity && buf.buffer) {  //Allocate memory
        size_t newCapacity = buf.capacity * MEM_INCREASE;
        T *tmp = new T[newCapacity];
        if (head < tail) {
            std::copy(buf.buffer + head, buf.buffer + tail, tmp + head);
        } else {
            //Since the buffer is looped, the tail can jump to the beginning of array, so tail can be < than head
            //In this case we'll expand looped buffer. Tail moves at the position after head;
            std::copy(buf.buffer + head, buf.buffer + buf.capacity, tmp + head);
            std::copy(buf.buffer, buf.buffer + tail, tmp + buf.capacity);
            tail = buf.capacity + tail;
        }
        buf.capacity = newCapacity;
        delete[]buf.buffer;
        buf.buffer = tmp;
    }
}

int main() {
    Queue<int> queue;

    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int op = 0, val = 0;
        std::cin >> op >> val;

        switch (op) {
            case 3: {
                queue.enqueue(val);
                break;
            }
            case 2: {
                int qValue = queue.dequeue();
                if (qValue != val) {
                    std::cout << "NO" << std::endl;
                    return 0;
                }
                break;
            }

            default:
                break;
        }
    }
    std::cout << "YES" << std::endl;
    return 0;
}
