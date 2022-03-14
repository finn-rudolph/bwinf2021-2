#include <vector>
#include <string>
#include <stdint.h>
#include <iostream>

template <typename T>
std::string to_binary_str(T number) {
    int length = sizeof (T) * 8;
    std::string binary(length, ' ');

    for (int i = 0; i < length; i++) {
        binary[length - i - 1] = ((number & (T) 1) + '0');
        number = number >> 1;
    }
    return binary;
}

template <typename T>
T to_number(std::string str) {
    T number = 0;
    for (char &bit: str) {
        number = (number << 1) | (bit - '0');
    }
    return number;
}

template <typename T>
std::vector<T> read_cards(int n) {
    std::vector<T> cards;
    for (int i = 0; i < n; i++) {
        std::string card; std::cin >> card;
        cards.push_back(to_number<T>(card));
    }
    return cards;
}

template <typename T>
void print_cards(std::vector<uint8_t> indices, std::vector<T> &cards) {
    std::cout << '\n';
    std::vector<T> solution;
    for (uint8_t i: indices) solution.push_back(cards[i]);
    sort(solution.begin(), solution.end());
    
    for (T card: solution) std::cout << to_binary_str<T>(card) << '\n';
    std::cout << std::endl;   
}
