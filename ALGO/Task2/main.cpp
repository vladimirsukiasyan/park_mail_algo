/*
 *Сукиасян Владимир, АПО-13
 *
 * Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
 * Для каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k], ближайшего по значению к B[i].
 * n ≤ 110000, m ≤ 1000.
 * Время работы поиска для каждого элемента B[i]: O(log(k)).

 Пример 1
 Ввод:
 3
 10 20 30

 Вывод:
 3
 9 15 35
 */

#include <iostream>

int findTwinInRange(const int *array, int twink, int n);

int binarySearch(const int *array, int start, int end, int twink);

int main() {
    int n, m;

    std::cin >> n;
    int *A = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> A[i];
    }

    std::cin >> m;
    int *B = new int[m];
    for (int i = 0; i < m; i++) {
        std::cin >> B[i];
        std::cout << findTwinInRange(A, B[i], n) << " ";
    }
    delete[]A;
    delete[]B;

    return 0;
}

int findTwinInRange(const int *array, int twink, int n) {
    int start = 0;
    int end = 0;

    //special cases
    if (twink < array[0]) {
        return 0;
    }
    if (twink > array[n - 1]) {
        return n - 1;
    }

    //Here we find the range, which consists of twink
    while (array[end] < twink) {
        start = end + 1;
        if (end * 2 < n) {
            end = !end ? 1 : end * 2;
        } else end = n - 1;
    }

    //As we have ordered array, we should search the index of the nearest twink by binary search
    int nearestIndex = binarySearch(array, start, end, twink);
    //Detect the nearest twink
    if (abs(array[nearestIndex] - twink) < abs(array[nearestIndex - 1] - twink)) {
        return nearestIndex;
    } else {
        return nearestIndex - 1;
    }
}

int binarySearch(const int *array, int start, int end, int twink) {
    int middle;
    while (start != end) {
        middle = (end + start) / 2;
        if (twink <= array[middle]) {
            end = middle;
        } else start = middle + 1;
    }
    return start;
}
