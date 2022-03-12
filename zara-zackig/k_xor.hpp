#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <functional>
#include <algorithm>
#include <stdint.h>
#include <iostream>
#include <cmath>
#include <unistd.h>
#include <thread>
#include "io.hpp"
using namespace std;

template <typename T>
void xor_combine(
    vector<T> &cards,
    int d,
    function<void (T&)> cb,
    uint8_t* used,
    uint8_t start,
    uint8_t end,
    T xor_val = 0
) {
    if (d == 0) {
        cb(xor_val);
        return;
    }

    for (uint8_t i = start; i < end; i++) {
        xor_val ^= cards[i];
        used[d - 1] = i;
        xor_combine<T>(cards, d - 1, cb, used, i + 1, cards.size(), xor_val);
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
    if (length <= 1 || bit == 0) return;

    long long a = 0, b = length - 1;
    while (a < b) {
        if ((values[a] >> bit) & (T) 1) {
            swap(values[a], values[b]);
            swap_ranges(indices + a * d, indices + a * d + d, indices + b * d);
            b -= 1;
        } else {
            a += 1;
        }
    }

    if (!((values[a] >> bit) & (T) 1)) a += 1;
    radix_sort_msd<T>(values, indices, a, d, bit - 1);
    radix_sort_msd<T>(values + a, indices + a * d, length - a, d, bit - 1);
}

template <typename T>
int bs(T* arr, long long length, T target) {
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
    if (k == 0) return 1;
    return ((double) n / (double) k) * (double) binom(n - 1, k - 1);
}

long long memory() {
    return sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGE_SIZE);
}

template <typename T, typename S>
vector<vector<S>> split_cards(vector<T> cards, int c) {
    vector<vector<S>> fragments(sizeof (T) / sizeof (S));
    for (T &card: cards) {
        string bin_string = to_binary_str<T>(card);
        for (int i = 0; i < bin_string.size(); i += c) {
            fragments[i / c].push_back(to_number<S>(bin_string.substr(i, c)));
        }
    }
    return fragments;
}

vector<int> assign_threads(long long num_comb, int cores, int n, int d) {
    vector<int> alloc(cores * 2, 0);
    int j = 1;
    long long min = num_comb / cores, sum = 0;
    for (int i = 0; j < cores; i++) {
        if (sum >= min * j) {
            alloc[j * 2] = i;
            alloc[j * 2 + 1] = sum;
            j += 1;
        } 
        sum += binom(n - i - 1, d - 1);
    }
    return alloc;
}

template <typename T>
set<vector<uint8_t>> xor_to_zero(vector<T> cards, int n, int k, int d) {
    long long num_comb = binom(n, d);

    T* values = new T[num_comb];
    uint8_t* indices = new uint8_t[num_comb * d];

    int cores = thread::hardware_concurrency();
    if (cores == 0) cores = sysconf(_SC_NPROCESSORS_ONLN);
    if (cores == 0) cores = 8;

    vector<int> alloc = assign_threads(num_comb, cores, n, d);
    cout << "Using " << cores << " threads\n\n";
    vector<thread> threads;

    for (int i = 0; i < cores; i++) {
        threads.emplace_back([i, &cards, &values, &indices, &n, &d, &cores, &alloc] {
            int pos = alloc[i * 2 + 1];
            uint8_t used[d];
            xor_combine<T>(cards, d, 
                [&values, &indices, &used, &pos, &d](T &xor_val) {
                    values[pos] = xor_val;
                    move(used, used + d, indices + pos * d);
                    pos += 1;
                },
                used, alloc[i * 2], i == cores - 1 ? n : alloc[i * 2 + 2]);
        });
    }

    for (thread &t: threads) t.join();

    cout << "Precomputed " << num_comb << " combinations, d = " << d << "\n";
    radix_sort_msd<T>(values, indices, num_comb, d);

    set<vector<uint8_t>> results;
    alloc = assign_threads(num_comb, cores, n, k - d);
    threads.clear();

    for (int i = 0; i < cores; i++) {
        threads.emplace_back([i, &cards, &values, &indices, &num_comb, &results, &n, &k, &d, &cores, &alloc] {
            uint8_t used[k - d];
            xor_combine<T>(cards, k - d,
                [&values, &indices, &results, &num_comb, &k, &d, &used](T &xor_val) {
                    int j = bs<T>(values, num_comb, xor_val);
                    if (j != -1) {
                        while (values[j - 1] == xor_val) j -= 1;

                        while (values[j] == xor_val) {
                            if (no_intersection(used, indices + j * d, k - d, d)) {
                                vector<uint8_t> res(used, used + k - d);
                                res.insert(res.end(), indices + j * d, indices + j * d + d);

                                sort(res.begin(), res.end());
                                results.insert(res);   
                            }
                            j += 1;
                        }
                    }
                },
                used, alloc[i * 2], i == cores - 1 ? n : alloc[i * 2 + 2]);
        });
    }

    for (thread &t: threads) t.join();

    delete[] values;
    delete[] indices;
    return results;
}

template <typename T, typename S>
void merge_results(vector<T> cards, int n, int k, int c, int d) {
    vector<vector<S>> fragments = split_cards<T, S>(cards, c);
    set<vector<uint8_t>> results;

    for (vector<S> &card_set: fragments) {
        set<vector<uint8_t>> partial = xor_to_zero<S>(card_set, n, k, d);
        if (results.empty()) {
            results = partial;
        } else {
            set<vector<uint8_t>> new_solutions;
            for (vector<uint8_t> comb: results) {
                if (partial.find(comb) != partial.end()) new_solutions.insert(comb);
            }
            results = new_solutions;
        }
    }
    print_cards<T>(*results.begin(), cards);
}

template <typename T>
void decide_parameters(int n, int k, int m) {
    vector<T> cards = read_cards<T>(n);

    long long memory_limit = memory() - (((long long) 1) << 31);
    cout << "Memory Limit: " << (memory_limit) / pow(10, 6) << " MB\n";

    int c = m;
    int d = k / 2;
    while (c > 8 && binom(n, d) * (c / 8 + d) > memory_limit) c /= 2;
    while (binom(n, d) * (c / 8 + d) > memory_limit) d -= 1;

    cout << "Divide cards into " << c << "-bit pieces\n";

    switch (c) {
        case 8: 
            merge_results<T, uint8_t>(cards, n, k, c, d);
            break;
        case 16: 
            merge_results<T, uint16_t>(cards, n, k, c, d);
            break;
        case 32: 
            merge_results<T, uint32_t>(cards, n, k, c, d);
            break;
        case 64: 
            merge_results<T, uint64_t>(cards, n, k, c, d);
            break;
        case 128: 
            merge_results<T, __uint128_t>(cards, n, k, c, d);
            break;
    }
}