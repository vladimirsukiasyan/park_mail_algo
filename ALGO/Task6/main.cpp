/*
 * Сукиасян Владимир, АПО-13
 *
 * Даны неотрицательные целые числа n, k и массив целых чисел из диапазона [0..109] размера n.
 * Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на
 * позиции с индексом k ∈[0..n-1] в отсортированном массиве.
 * Напишите нерекурсивный алгоритм.
 * Требования к дополнительной памяти: O(n).
 * Требуемое среднее время работы: O(n).
 * Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.
 * Описание для случая прохода от начала массива к концу:
 * Выбирается опорный элемент.
 * Опорный элемент меняется с последним элементом массива.
 * Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного.
 * Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы.
 * Последним элементом лежит опорный.
 * Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
 * Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
 * Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j.
 * Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
 * В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.
 *
 * Реализуйте стратегию выбора опорного элемента “случайный элемент”.
 * Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
 */

#include <iostream>
#include <functional>

template<typename T, typename Comparator = std::less<T>>
int partition(T *arr, int l, int r, Comparator cmp = Comparator()) {
    if (l == r) {
        return l;
    }
    int piv_index = l + rand() % (r - l + 1);
    std::swap(arr[piv_index], arr[l]);
    T pivot = arr[l];

    int i = l + 1;
    int j = r;

    while (true) {
        while (i <= r && cmp(arr[i], pivot))
            i++;
        while (cmp(pivot, arr[j]))
            j--;
        if (i >= j) {
            std::swap(arr[l], arr[j]);
            return j;
        }

        std::swap(arr[i], arr[j]);
        i++;
        j--;
    }
}

template<typename T, typename Comparator = std::less<T>>
T kth_statistic(T *arr, int k, int l, int r, Comparator cmp = Comparator()) {
    int pivot_index=-1;
    while(pivot_index!=k){
        pivot_index=partition(arr,l,r,cmp);
        if(pivot_index>k){
            r=pivot_index-1;
        }
        else{
            l=pivot_index+1;
        }
    }
    return arr[pivot_index];
}

int main(int argc, const char *argv[]) {
    srand((unsigned) time(nullptr));
    int n, k;
    std::cin >> n >> k;

    int *arr = new int[n];

    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    std::cout << kth_statistic<int>(arr, k, 0, n-1) << std::endl;

    delete []arr;
    return 0;
}