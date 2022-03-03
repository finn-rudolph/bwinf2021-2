#include <bits/stdc++.h>
using namespace std;

template <typename T> vector<T> read_cards(int n);

template <typename T> vector<T> triplet(vector<T> &cards);

template <typename T> void print_cards(vector<T> &cards);

int main() {
    int n, k, m;
    cin >> n >> k >> m;
    
    switch (m) {
        case 32: {
            auto cards = read_cards<uint32_t>(n);
            vector<uint32_t> res = triplet<uint32_t>(cards);
            print_cards<uint32_t>(res);
            break;
        }
        case 64: {
            auto cards = read_cards<uint64_t>(n);
            vector<uint64_t> res = triplet<uint64_t>(cards);
            print_cards<uint64_t>(res);
            break;
        }
        case 128: {
            auto cards = read_cards<__uint128_t>(n);
            vector<__uint128_t> res = triplet<__uint128_t>(cards);
            print_cards<__uint128_t>(res);
            break;
        }
    }
}

template <typename T> vector<T> read_cards(int n) {
    vector<T> cards;
    for (int i = 0; i < n; i++) {
        string card; cin >> card;
        T number;
        for (char &bit: card) {
            number = (number << 1) | (bit - '0');
        }
        cards.push_back(number);
    }
    return cards;
}

template <typename T> vector<T> triplet(vector<T> &cards) {
    unordered_map<T, int> cards_map;
    for (int i = 0; i < cards.size(); i++) {
        cards_map[cards[i]] = i;
    }
    for (T &card1: cards) {
        for (T &card2: cards) {
            T card3 = card1 xor card2;
            if (card1 != card2 && cards_map.find(card3) != cards_map.end()) {
                return { card1, card2, card3 };
            }
        }
    }
}

template <typename T> void print_cards(vector<T> &cards) {
    int length = sizeof (cards[0]) * 8;

    for (T card: cards) {
        for (int i = 0; i < length; i++) {
            card = card >> 1;
            cout << (int) (card % 2);
        }
        cout << '\n';
    }
}