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
#include <cassert>
#include "io.hpp"

template <typename T>
void xor_combine(
    std::vector<T> &cards,
    int a,
    std::function<void (T&)> cb,
    uint8_t* used,
    uint8_t start,
    uint8_t end,
    T xor_val = 0
) {
    if (a == 0) {
        cb(xor_val);
        return;
    }

    for (uint8_t i = start; i < end; i++) {
        xor_val ^= cards[i];
        used[a - 1] = i;
        xor_combine<T>(cards, a - 1, cb, used, i + 1, cards.size(), xor_val);
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
void radix_sort_msd(T* val, uint8_t* ind, long long length, int d, int t_depth, int h) {
    if (length <= 1 || h == 0) return;

    long long u = 0, v = length - 1;
    while (u < v) {
        if ((val[u] >> h) & (T) 1) {
            std::swap(val[u], val[v]);
            std::swap_ranges(ind + u * d, ind + u * d + d, ind + v * d);
            v -= 1;
        } else {
            u += 1;
        }
    }

    if (!((val[u] >> h) & (T) 1)) u += 1;
    if (t_depth != 0) {
        std::thread t1([&] {
            radix_sort_msd<T>(val, ind, u, d, t_depth - 1, h - 1);
        });
        std::thread t2([&] {
            radix_sort_msd<T>(val + u, ind + u * d, length - u, d, t_depth - 1, h - 1);
        });
        t1.join();
        t2.join();
    } else {
        radix_sort_msd<T>(val, ind, u, d, t_depth, h - 1);
        radix_sort_msd<T>(val + u, ind + u * d, length - u, d, t_depth, h - 1);
    }
}

template <typename T>
long long bs(T* val, long long length, T target) {
    long long u = 0, v = length - 1;

    while (u < v) {
        int mid = (u + v) / 2;
        if (val[mid] < target) u = mid + 1;
        else if (val[mid] > target) v = mid - 1;
        else return mid;
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

template <typename T>
bool is_valid(std::vector<uint8_t> &res, std::vector<T> &cards) {
    T xor_val = 0;
    for (uint8_t i: res) xor_val ^= cards[i];
    return xor_val == 0 ? 1 : 0;
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
void xor_to_zero(std::vector<T> cards, int n, int k, long long mem_limit) {
    if (mem_limit == 0) mem_limit = memory() - (((long long) 1) << 31);
    std::cout << "Memory Limit: " << (mem_limit) / pow(10, 6) << " MB\n";

    int d = k / 2;
    while (binom(n, d) * (sizeof (T) + d) > mem_limit) d -= 1;
    long long num_comb = binom(n, d);

    auto begin = std::chrono::system_clock::now();

    T* val = new T[num_comb];
    uint8_t* ind = new uint8_t[num_comb * d];

    int cores = std::thread::hardware_concurrency();
    if (cores == 0) cores = sysconf(_SC_NPROCESSORS_ONLN);
    if (cores == 0) cores = 8;

    std::vector<int> alloc = assign_threads(num_comb, cores, n, d);
    std::cout << "Using " << cores << " threads\n";
    std::vector<std::thread> threads;

    for (int i = 0; i < cores; i++) {
        threads.emplace_back([i, &cards, &val, &ind, &n, &d, &cores, &alloc] {
            int pos = alloc[i * 2 + 1];
            uint8_t used[d];
            xor_combine<T>(cards, d, 
                [&val, &ind, &used, &pos, &d](T &xor_val) {
                    val[pos] = xor_val;
                    std::copy(used, used + d, ind + pos * d);
                    pos += 1;
                },
                used, alloc[i * 2], i == cores - 1 ? n : alloc[i * 2 + 2]);
        });
    }

    for (std::thread &t: threads) t.join();

    std::cout << "Precomputed " << num_comb << " combinations, d = " << d << " after " 
        << ((std::chrono::duration<float>) (std::chrono::system_clock::now() - begin)).count() << " s \n";

    radix_sort_msd<T>(val, ind, num_comb, d, ceil(log2(cores)), sizeof (T) * 8 - 1);
    std::cout << "Sorted after " << ((std::chrono::duration<float>) 
        (std::chrono::system_clock::now() - begin)).count() << " s \n";

    alloc = assign_threads(num_comb, cores, n, k - d);
    threads.clear();
    std::atomic_bool found(false);

    for (int i = 0; i < cores; i++) {
        threads.emplace_back([i, &cards, &val, &ind, &num_comb, 
            &n, &k, &d, &cores, &alloc, &begin, &found] {
            uint8_t used[k - d];
            xor_combine<T>(cards, k - d,
                [&cards, &val, &ind, &num_comb, &k, &d, &used, &begin, &found](T &xor_val) {
                    if (found) return;
                    long long j = bs<T>(val, num_comb, xor_val);
                    if (j != -1) {
                        while (j > 0 && val[j - 1] == xor_val) j -= 1;      

                        while (val[j] == xor_val && j < num_comb) {
                            if (no_intersection(used, ind + j * d, k - d, d) && !found) {
                                found.store(true);

                                std::vector<uint8_t> res(used, used + (k - d));
                                res.insert(res.end(), ind + j * d, ind + j * d + d);
                                assert(is_valid<T>(res, cards));
                                
                                print_cards(res, cards);
                                std::cout << ((std::chrono::duration<float>) 
                                    (std::chrono::system_clock::now() - begin)).count() 
                                    << " s \n";

                                delete[] ind;
                                delete[] val;
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

    std::cout << "No solution found\n";
    delete[] val;
    delete[] ind;
}