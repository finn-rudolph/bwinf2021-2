#include <vector>
#include <string>
#include <stdint.h>
#include <iostream>
using namespace std;

template <typename T>
string to_binary_str(T number) {
    int length = sizeof (T) * 8;
    string binary(length, ' ');

    for (int i = 0; i < length; i++) {
        binary[length - i - 1] = ((number & (T) 1) + '0');
        number = number >> 1;
    }
    return binary;
}

template <typename T>
T to_number(string str) {
    T number = 0;
    for (char &bit: str) {
        number = (number << 1) | (bit - '0');
    }
    return number;
}

template <typename T>
vector<T> read_cards(int n) {
    vector<T> cards;
    for (int i = 0; i < n; i++) {
        string card; cin >> card;
        cards.push_back(to_number<T>(card));
    }
    return cards;
}

template <typename T>
void print_cards(vector<uint8_t> indices, vector<T> &cards) {
    cout << '\n';
    for (uint8_t i: indices) {
        cout << to_binary_str<T>(cards[i]) << " (Z. " << ((int) i + 2)  << ")" << '\n';
    }
    cout << endl;   
}
