#include <bits/stdc++.h>
using namespace std;

template <typename T>
void print_binary(T number) {
    int length = sizeof (number) * 8;
    string binary(length, ' ');

    for (int i = 0; i < length; i++) {
        binary[length - i - 1] = ((number % 2) + '0');
        number = number >> 1;
    }
    cout << binary;
}

template <typename T>
vector<T> read_cards(int n) {
    vector<T> cards;

    for (int i = 0; i < n; i++) {
        string card; cin >> card;
        T number = 0;
        for (char &bit: card) {
            number = (number << 1) | (bit - '0');
        }
        cards.push_back(number);
    }
    return cards;
}

template <typename T>
void print_cards(vector<uint8_t> indices, vector<T> &cards) {
    for (uint8_t i: indices) {
        print_binary<T>(cards[i]);
        cout << " (Z. " << ((int) i + 2)  << ")" << '\n';
    }
    cout << endl;   
}

template <typename T>
void print_map(unordered_map<T, uint8_t*> &xor_map, vector<T> &cards) {
    for (auto [xor_value, components]: xor_map) {
        print_binary(xor_value);
        cout << " -> ";
        
        for (int i = 0; i < 1; i++) {
            print_binary<T>(cards[components[i]]);
            cout << " ";
        }
        cout << '\n';
    }
    cout << endl;
}
