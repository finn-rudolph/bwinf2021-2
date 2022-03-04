#include <bits/stdc++.h>
using namespace std;

template <typename T>
void xor_combine(
    vector<T> &cards,
    int d,
    function<void (T, vector<uint8_t>&)> cb,
    vector<uint8_t> &used,
    T xor_value = 0,
    uint8_t start = 0
) {
    if (d == 0) {
        cb(xor_value, used);
        return;
    }

    for (uint8_t i = start; i < cards.size(); i++) {
        xor_value = xor_value xor cards[i];
        used.push_back(i);
        xor_combine<T>(cards, d - 1, cb, used, xor_value, i + 1);

        xor_value = xor_value xor cards[i];
        used.pop_back();
    }
}

template <typename T>
vector<T> find_k_xor(vector<T> &cards, int k) {
    int d = k / 2;
    unordered_map<T, uint8_t*> xor_map;

    vector<uint8_t> used = {};
    xor_combine<T>(cards, d, 
        [&xor_map](T xor_val, vector<uint8_t> &used) {
            uint8_t* used_arr = new uint8_t[used.size()];
            copy(used.begin(), used.end(), used_arr);
            xor_map[xor_val] = used_arr;
        }, used);
}

template <typename T>
void delete_map(unordered_map<T, uint8_t*> xor_map) {
    for (auto [ignore, components]: xor_map) {
        delete components;
    }
}