#include <bits/stdc++.h>
#include "io.hpp"
using namespace std;

template <typename T>
struct xor_comb {
    T value;
    uint8_t* cards; // indices
};

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

bool no_intersection(vector<uint8_t> &vec, uint8_t* arr, int length) {
    unordered_set<uint8_t> arr_set(arr, arr + length);
    for (uint8_t &number: vec) {
        if (arr_set.find(number) != arr_set.end()) {
            return false;
        }
    }
    return true;
}

template <typename T>
void radix_sort_lsd(vector<xor_comb<T>> &arr) {
    vector<xor_comb<T>> zeros;
    vector<xor_comb<T>> ones;

    for (int i = 0; i < sizeof (T) * 8; i++) {
        for (xor_comb<T> &comb: arr) {
            ((comb.value >> i) & (T) 1) 
                ? ones.push_back(move(comb)) 
                : zeros.push_back(move(comb));
        }

        zeros.insert(zeros.end(), ones.begin(), ones.end());
        swap(zeros, arr);
        zeros.clear();
        ones.clear();
    }
}

template <typename T>
int bs(vector<xor_comb<T>> &arr, T target) {
    int a = 0, b = arr.size() - 1;

    while (b > a) {
        int mid = (a + b) / 2;
        if (arr[mid].value == target) return mid;
        else if (arr[mid].value < target) a = mid + 1;
        else b = mid - 1;
    }
    return -1;
}

template <typename T>
void delete_xors(vector<xor_comb<T>> xors) {
    for (auto [ignore, cards]: xors) {
        delete cards;
    }
}

template <typename T>
void find_k_xor(int n, int k) {
    vector<T> cards = read_cards<T>(n);
    int d = k / 2;

    vector<xor_comb<T>> xors;
    vector<uint8_t> used;

    xor_combine<T>(cards, d, 
        [&xors](T xor_val, vector<uint8_t> &used) {
            uint8_t* used_cards = new uint8_t[used.size()];           
            copy(used.begin(), used.end(), used_cards);
            
            xor_comb<T> comb = { xor_val, used_cards };
            xors.push_back(comb);
        }, 
        used);

    used.clear();
    radix_sort_lsd<T>(xors);
    set<vector<uint8_t>> results;

    xor_combine<T>(cards, k - d,
        [&xors, &results, &d](T xor_val, vector<uint8_t> &used) {
            int i = bs<T>(xors, xor_val);
            if (i != -1 && no_intersection(used, xors[i].cards, d)) {
                vector<uint8_t> used_cards(used.begin(), used.end());
                used_cards.insert(used_cards.end(), xors[i].cards, xors[i].cards + d);

                sort(used_cards.begin(), used_cards.end());
                results.insert(used_cards);    
            }
        },
        used);

    print_cards<T>(*results.begin(), cards);
    delete_xors<T>(xors);
}