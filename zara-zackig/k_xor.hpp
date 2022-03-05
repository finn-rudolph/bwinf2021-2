#include <bits/stdc++.h>
#include "io.hpp"
using namespace std;

template <typename T>
void xor_combine(
    vector<T> &cards,
    int d,
    function<void (T, vector<uint8_t>&)> cb,
    vector<uint8_t> &used,
    T xor_val = 0,
    uint8_t start = 0
) {
    if (d == 0) {
        cb(xor_val, used);
        return;
    }

    for (uint8_t i = start; i < cards.size(); i++) {
        xor_val = xor_val xor cards[i];
        used.push_back(i);
        xor_combine<T>(cards, d - 1, cb, used, xor_val, i + 1);

        xor_val = xor_val xor cards[i];
        used.pop_back();
    }
}

bool no_intersection(vector<uint8_t> vec, uint8_t* arr, int length) {
    unordered_set<uint8_t> arr_set(arr, arr + length);
    for (uint8_t &number: vec) {
        if (arr_set.find(number) != arr_set.end()) {
            return false;
        }
    }
    return true;
}

template <typename T>
void delete_map(unordered_map<T, uint8_t*> xor_map) {
    for (auto [ignore, components]: xor_map) {
        delete components;
    }
}

template <typename T>
void find_k_xor(int n, int k) {
    vector<T> cards = read_cards<T>(n);
    int d = k / 2;

    unordered_map<T, uint8_t*> xor_map;
    vector<uint8_t> used = {};

    xor_combine<T>(cards, d, 
        [&xor_map](T xor_val, vector<uint8_t> &used) {
            uint8_t* used_arr = new uint8_t[used.size()];           
            copy(used.begin(), used.end(), used_arr);
            xor_map[xor_val] = used_arr;
        }, 
        used);

    // Use different data structure for faster comparison
    used.clear(); 
    set<vector<uint8_t>> results;

    xor_combine<T>(cards, k - d,
        [&xor_map, &results, &k, &d](T xor_val, vector<uint8_t> &used) {
            if (xor_map.find(xor_val) != xor_map.end() && 
                no_intersection(used, xor_map[xor_val], k)
            ) {
                vector<uint8_t> comb(used.begin(), used.end());
                comb.insert(comb.end(), xor_map[xor_val], xor_map[xor_val] + d);

                sort(comb.begin(), comb.end());   
                results.insert(comb);    
            }
        },
        used);

    print_cards<T>(*results.begin(), cards);
    delete_map(xor_map);
}