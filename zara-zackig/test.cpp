#include <vector>
#include <cmath>
#include <algorithm>
#include "test.hpp"
#include "k_xor.hpp"
using namespace std;

int main () {
    typedef __uint128_t N;
    int n, k; cin >> n >> k;

    vector<N> cards(n - 1);

    srand(time(NULL));
    for (int i = 0; i < n - 1; i++) {
        cards[i] = random_T<N>();
    }

    N xor_card = 0;
    for (int i = 0; i < k - 1; i++) xor_card ^= cards[i];
    cards.push_back(xor_card);

    random_shuffle(cards.begin(), cards.end());

    xor_to_zero<N>(cards, n, k);
}