#include <vector>
#include <cmath>
#include <algorithm>
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
void test(int n, int k) {
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

    xor_to_zero<T>(cards, n, k);

}

int main () {
    int n, k, m; std::cin >> n >> k >> m;

    switch (m) {
        case 8:
            test<uint8_t>(n, k);
            break;
        case 16:
            test<uint16_t>(n, k);
            break;
        case 32:
            test<uint32_t>(n, k);
            break;
        case 64:
            test<uint64_t>(n, k);
            break;
        case 128:
            test<__uint128_t>(n, k);
            break;
        default:
            std::cout << "Invalid number of bits\n";
    }
}