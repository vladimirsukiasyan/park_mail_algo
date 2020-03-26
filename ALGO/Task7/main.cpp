#include <iostream>
#include <cstring>
#include <vector>

/*
 * Сукиасян Владимир, группа АПО-13
 *
 * Дан массив строк. Количество строк не больше 100000. Отсортировать массив методом поразрядной сортировки MSD по символам.
 * Размер алфавита - 256 символов. Последний символ строки = ‘0’.
 *
 */

using  namespace std;

const int abc_power = 256;

void MSDSort(char **arr, int n, int byte = 0);

void counting_sort(char **pString, int n, int *pInt, int byte);

/******************************************************************************/

int main() {
    std::vector<char *> strokes;

    std::string str;
    while(true) {
        std::getline(std::cin, str);

        if (str.empty()) {
            break;
        }

        char *c_str = new char[str.length() + 1];
        strcpy(c_str, str.c_str());

        strokes.push_back(c_str);
    }

    MSDSort(&strokes[0], (int)strokes.size());

    for (auto &i : strokes) {
        std::cout << i << std::endl;
    }

    for (auto &stroke : strokes)
        delete stroke;

    return 0;
}

void MSDSort(char **arr, int n, int byte){
    int *groups = new int[abc_power + 1];

    groups[abc_power] = n;

    counting_sort(arr, n, groups, byte);

    for (int i = 0; i < abc_power; ++i) {
        int group_size = groups[i + 1] - groups[i];
        if (group_size > 1) {
            MSDSort(&arr[groups[i]], group_size, byte + 1);
        }
    }

    delete[] groups;
}

void counting_sort(char **arr, int n, int *cnt, int byte) {
    for (int i = 0; i < abc_power; ++i) {
        cnt[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        ++cnt[arr[i][byte]];
    }

    int sum = 0;
    for (int i = 0; i < abc_power; ++i) {
        int tmp = cnt[i];
        cnt[i] = sum;
        sum += tmp;
    }

    char **res = new char*[n];

    for (int i = 0; i < n; ++i) {
        res[cnt[arr[i][byte]]++] = arr[i];
    }

    memcpy(arr, res, n * sizeof(char*));

    delete[] res;
}
