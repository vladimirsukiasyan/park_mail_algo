#include <iostream>

using namespace std;

int main() {
    int a_size,
            b_size,
            i,
            k,
            d = 0,
            count = 0;

    cin >> a_size;
    int *a = new int[a_size];
    for (i = 0; i < a_size; i++)
        cin >> a[i];

    cin >> b_size;
    int *b = new int[b_size];
    for (i = 0; i < b_size; i++)
        cin >> b[i];

    cin >> k;
    if (a_size <= b_size) {
        for (i = b_size - 1; i >= 0;) {
            if (b[i] + a[d] < k)
                d++;
            if (b[i] + a[d] == k) {
                i--;
                count++;
            }
            if (b[i] + a[d] > k) {
                i--;
            }
        }
    } else {
        for (i = a_size - 1; i > 0;) {
            if (a[i] + b[d]< k)
                d++;
            if (a[i] == k - b[d]) {
                count++;
                i--;
            }
            if (a[i] > k - b[d])
                i--;
        }
    }
    cout << count;

    delete[]a;
    delete[]b;
    return 0;
}