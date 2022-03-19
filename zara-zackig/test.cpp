#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include "k_xor.hpp"

template<typename T>
T random_T() {
    if (sizeof (T) <= 4) return rand();
    T num = 0;
    for (int i = 0; i < sizeof (T) / 4; i++) {
        num = (num << 32) | (T) rand(); //
    }
    return num;
}  

template <typename T>
void test(int n, int k, long long mem_limit) {
    std::vector<T> cards(n - 1);

    std::srand(time(NULL));
    for (int i = 0; i < n - 1; i++) {
        cards[i] = random_T<T>();
    }

    T xor_card = 0;
    for (int i = 0; i < k - 1; i++) xor_card ^= cards[i];
    cards.push_back(xor_card);

    std::cout << "Generated cards:\n";
    for (T &card: cards) std::cout << to_binary_str<T>(card) << '\n';
    std::cout << std::endl;

    std::random_shuffle(cards.begin(), cards.end());

    xor_to_zero<T>(cards, n, k, mem_limit);

}

int main (int argc, char* argv[]) {
    long long mem_limit = 0;
    if (argc > 2) {
        std::cout << "Too many arguments. Run with: ./test [memory limit in megabytes]\n";
        exit(EXIT_FAILURE);
    } else if (argc == 2) {
        mem_limit = std::stold(argv[1]) * 1000000;
    }
    
    std::cout << "n, k, m: ";
    int n, k, m;
    std::cin >> n >> k >> m;

    if (n > 255) {
        std::cout << "Limit for n: 255 (using uint8_t for indexing cards)";
        exit(EXIT_FAILURE);
    }

    switch (m) {
        case 8:
            test<uint8_t>(n, k, mem_limit);
            break;
        case 16:
            test<uint16_t>(n, k, mem_limit);
            break;
        case 32:
            test<uint32_t>(n, k, mem_limit);
            break;
        case 64:
            test<uint64_t>(n, k, mem_limit);
            break;
        case 128:
            test<__uint128_t>(n, k, mem_limit);
            break;
        default:
            std::cout << "Invalid number of bits\n";
    }
}