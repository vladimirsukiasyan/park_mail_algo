/*
 * Сукиасян Владимир, АПО-13
 *
 * В супермаркете решили оптимизировать показ рекламы. Известно расписание прихода и ухода покупателей (два целых числа).
 * Каждому покупателю необходимо показать минимум 2 рекламы. Рекламу можно транслировать только в целочисленные моменты времени.
 * Покупатель может видеть рекламу от момента прихода до момента ухода из магазина.
 * В каждый момент времени может показываться только одна реклама. Считается, что реклама показывается мгновенно.
 * Если реклама показывается в момент ухода или прихода, то считается, что посетитель успел её посмотреть.
 * Требуется определить минимальное число показов рекламы.
 */


#include <iostream>
#include <cstring>

template <typename T>
void Merge(const T *firstArr, int len1, const T *secondArr, int len2, T *result, std::less<T> cmp);

template <typename T>
void MergeSort(T *arr, int n);

struct Client{
    int begin=0;
    int end=0;
    int firstAdIndex=-1;
    int secondAdIndex=-1;
};

int main() {
    int n;
    std::cin >> n;

    Client *clients = new Client[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> clients[i].begin >> clients[i].end;
    }
    MergeSort<Client>(clients, n);

    Client *prevClient=clients;
    prevClient->firstAdIndex=prevClient->end-1;
    prevClient->secondAdIndex=prevClient->end;
    int count=2;
    for(int i=1;i<n;++i){
        if(clients[i].begin<=prevClient->firstAdIndex) {
            clients[i].firstAdIndex = prevClient->firstAdIndex;
        }
        if(clients[i].begin<=prevClient->secondAdIndex) {
            if(clients[i].firstAdIndex!=-1){
                clients[i].secondAdIndex=prevClient->secondAdIndex;
            }
            else{
                clients[i].firstAdIndex=prevClient->secondAdIndex;
            }
        }
        if(clients[i].firstAdIndex==-1){
            clients[i].firstAdIndex=clients[i].end-1;
            count++;
        }
        if(clients[i].secondAdIndex==-1){
            clients[i].secondAdIndex=clients[i].end;
            count++;
        }
        prevClient=clients+i;
    }

    std::cout<<count;
    delete [] clients;


    return 0;
}

class ClientComparator{
public:
    bool operator()(const Client& l,const Client& r){
        if(l.end==r.end){
            return l.begin>=r.begin;
        }
        return l.end<=r.end;
    }
};

template <typename T>
void MergeSort(T *arr, int n) {
    if (n <= 1) {
        return;
    }
    int firstLen = n / 2;
    int secondLen = n - firstLen;

    MergeSort(arr, firstLen);
    MergeSort(arr + firstLen, secondLen);

    T *mergedArray = new T[n];
    Merge(arr, firstLen, arr + firstLen, secondLen, mergedArray, ClientComparator());
    memmove(arr, mergedArray, sizeof(T) * n);
    delete[] mergedArray;
}

template<typename T, typename Comparator>
void Merge(const T *firstArr, int len1, const T *secondArr, int len2, T *result, Comparator cmp) {
    int i = 0, j = 0, k = 0;
    while (i < len1 || j < len2) {
        if(i==len1){
            while (j < len2) {
                result[k++] = secondArr[j++];
            }
        }
        else if(j == len2){
            while (i < len1) {
                result[k++] = firstArr[i++];
            }
        }
        else{
            result[k++] = cmp(firstArr[i],secondArr[j]) ? firstArr[i++] : secondArr[j++];
        }
    }
}
