#include <vector>
#include <set>
#include <unordered_set>
#include <functional>
#include <algorithm>
#include <stdint.h>
#include <iostream>
#include <cmath>
#include <unistd.h>
#include <thread>
#include <atomic>
#include <chrono>
#include "io.hpp"

template <typename T>
void xor_combine(
    std::vector<T> &cards,
    int d,
    std::function<void (T&)> cb,
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
    std::unordered_set<uint8_t> arr_set(arr2, arr2 + len2);
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
            std::swap(values[a], values[b]);
            std::swap_ranges(indices + a * d, indices + a * d + d, indices + b * d);
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
long long bs(T* arr, long long length, T target) {
    long long a = 0, b = length - 1;

    while (a < b) {
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

std::vector<int> assign_threads(long long num_comb, int cores, int n, int d) {
    std::vector<int> alloc(cores * 2, 0);
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
void xor_to_zero(std::vector<T> cards, int n, int k) {
    long long memory_limit = memory() - (((long long) 1) << 31);
    std::cout << "Memory Limit: " << (memory_limit) / pow(10, 6) << " MB\n";

    int d = k / 2;
    while (binom(n, d) * (sizeof (T) + d) > memory_limit) d -= 1;
    long long num_comb = binom(n, d);

    auto begin = std::chrono::system_clock::now();

    T* values = new T[num_comb];
    uint8_t* indices = new uint8_t[num_comb * d];

    int cores = std::thread::hardware_concurrency();
    if (cores == 0) cores = sysconf(_SC_NPROCESSORS_ONLN);
    if (cores == 0) cores = 8;

    std::vector<int> alloc = assign_threads(num_comb, cores, n, d);
    std::cout << "Using " << cores << " threads\n";
    std::vector<std::thread> threads;

    for (int i = 0; i < cores; i++) {
        threads.emplace_back([i, &cards, &values, &indices, &n, &d, &cores, &alloc] {
            int pos = alloc[i * 2 + 1];
            uint8_t used[d];
            xor_combine<T>(cards, d, 
                [&values, &indices, &used, &pos, &d](T &xor_val) {
                    values[pos] = xor_val;
                    std::move(used, used + d, indices + pos * d);
                    pos += 1;
                },
                used, alloc[i * 2], i == cores - 1 ? n : alloc[i * 2 + 2]);
        });
    }

    for (std::thread &t: threads) t.join();

    std::cout << "Precomputed " << num_comb << " combinations, d = " << d << "\n";
    radix_sort_msd<T>(values, indices, num_comb, d);
    std::cout << "Sorted\n";

    alloc = assign_threads(num_comb, cores, n, k - d);
    threads.clear();
    std::atomic_bool found(false);

    for (int i = 0; i < cores; i++) {
        threads.emplace_back([i, &cards, &values, &indices, &num_comb, &n, &k, &d, &cores, &alloc, &begin, &found] {
            uint8_t used[k - d];
            xor_combine<T>(cards, k - d,
                [&cards, &values, &indices, &num_comb, &k, &d, &used, &begin, &found](T &xor_val) {
                    if (found) return;
                    long long j = bs<T>(values, num_comb, xor_val);
                    if (j != -1) {
                        while (j > 0 && values[j - 1] == xor_val) j -= 1;      

                        while (values[j] == xor_val && j < num_comb) {
                            if (no_intersection(used, indices + j * d, k - d, d) && !found) {
                                found.store(true);

                                std::vector<uint8_t> res(used, used + (k - d));
                                res.insert(res.end(), indices+ j * d, indices + j * d + d);
                                print_cards(res, cards);
                                std::cout << ((std::chrono::duration<float>) 
                                    (std::chrono::system_clock::now() - begin)).count() << " s \n";

                                delete[] indices;
                                delete[] values;
                                exit(EXIT_SUCCESS);
                            }
                            j += 1;
                        }
                    }
                },
                used, alloc[i * 2], i == cores - 1 ? n : alloc[i * 2 + 2]);
        });
    }

    for (std::thread &t: threads) t.join();

    delete[] values;
    delete[] indices;
}