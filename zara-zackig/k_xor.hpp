#include <vector>
#include <set>
#include <unordered_set>
#include <functional>
#include <algorithm>
#include <stdint.h>
#include <iostream>
#include <cstring>
#include "io.hpp"
using namespace std;

template <typename T>
void xor_combine(
    vector<T> &cards,
    int d,
    function<void (T)> cb,
    uint8_t* used,
    T xor_val = 0,
    uint8_t start = 0
) {
    if (d == 0) {
        cb(xor_val);
        return;
    }

    for (uint8_t i = start; i < cards.size(); i++) {
        xor_val ^= cards[i];
        used[d - 1] = i;
        xor_combine<T>(cards, d - 1, cb, used, xor_val, i + 1);
        xor_val ^= cards[i];
    }
}

bool no_intersection(uint8_t* arr1, uint8_t* arr2, int len1, int len2) {
    unordered_set<uint8_t> arr_set(arr2, arr2 + len2);
    for (int i = 0; i < len1; i++) {
        if (arr_set.find(arr1[i]) != arr_set.end()) {
            return false;
        }
    }
    return true;
}

template <typename T>
void radix_sort_msd(T* values, uint8_t* indices, long long length, int d, int bit = sizeof (T) * 8 - 1) {
    if (length <= 1) return;

    long long a = 0, b = length - 1;
    while (a != b) {
        if ((values[a] >> bit) & (T) 1) {
            swap(values[a], values[b]);
            swap_ranges(indices + a * d, indices + a * d + d, indices + b * d);
            b -= 1;
        } else {
            a += 1;
        }
    }

    radix_sort_msd<T>(values, indices, a, d, bit - 1);
    radix_sort_msd<T>(values + a, indices + a * d, length - a, d, bit - 1);
}

template <typename T>
int bs(T* &arr, long long length, T target) {
    int a = 0, b = length - 1;

    while (b > a) {
        int mid = (a + b) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) a = mid + 1;
        else b = mid - 1;
    }
    return -1;
}

long long binom(int n, int k) {
    if (k == 1) return n;
    return ((double) n / (double) k) * (double) binom(n - 1, k - 1);
}

template <typename T>
void find_k_xor(int n, int k, int m) {
    vector<T> cards = read_cards<T>(n);

    long long memory_limit = ((long long) 1) << 32;
    int d = k / 2;
    while (binom(n, d) * (m / 8 + d) > memory_limit) d -= 1;

    long long num_comb = binom(n, d);
    cout << "Berechne das xor von " << num_comb 
        << " Teilmengen mit Größe d = " << d << " vorab.\n";

    T* values = new T[num_comb];
    uint8_t* indices = new uint8_t[num_comb * d];
    int length = 0;
    uint8_t used[k - d];

    xor_combine<T>(cards, d, 
        [&values, &indices, &used, &length, &d](T xor_val) {
            values[length] = xor_val;
            move(used, used + d, indices + length * d);
            length += 1;
        }, 
        used);

    radix_sort_msd<T>(values, indices, num_comb, d);

    set<vector<uint8_t>> results;

    xor_combine<T>(cards, k - d,
        [&values, &indices, &results, &used, &num_comb, &k, &d](T xor_val) {
            int i = bs<T>(values, num_comb, xor_val);
            if (i != -1 && no_intersection(used, indices + i * d, k - d, d)) {
                vector<uint8_t> used_cards(used, used + k - d);
                used_cards.insert(used_cards.end(), indices + i * d, indices + i * d + d);

                sort(used_cards.begin(), used_cards.end());
                results.insert(used_cards);    
            }
        },
        used);

    print_cards<T>(*results.begin(), cards);
    delete[] values;
    delete[] indices;
}