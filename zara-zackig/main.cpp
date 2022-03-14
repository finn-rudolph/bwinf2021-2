#include <iostream>
#include "k_xor.hpp"

int main() {
    int n, k, m;
    std::cin >> n >> k >> m;
    k += 1;
    
    switch (m) {
        case 8: {
            std::vector<uint8_t> cards = read_cards<uint8_t>(n);
            xor_to_zero<uint8_t>(cards, n, k);
            break;
        }
        case 16: {
            std::vector<uint16_t> cards = read_cards<uint16_t>(n);
            xor_to_zero<uint16_t>(cards, n, k);
            break;
        }
        case 32: {
            std::vector<uint32_t> cards = read_cards<uint32_t>(n);
            xor_to_zero<uint32_t>(cards, n, k);
            break;
        }
        case 64: {
            std::vector<uint64_t> cards = read_cards<uint64_t>(n);
            xor_to_zero<uint64_t>(cards, n, k);
            break;
        }
        case 128: {
            std::vector<__uint128_t> cards = read_cards<__uint128_t>(n);
            xor_to_zero<__uint128_t>(cards, n, k);
            break;
        }
    }
}
