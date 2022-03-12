#include <vector>
#include <ctime>
#include <cmath>
#include "test.hpp"
#include "k_xor.hpp"
using namespace std;

int main () {
    typedef uint64_t N;
    int split = 8;
    int tests, n, k; cin >> tests >> n >> k;

    vector<int> times;
    vector<bool> validity;
    
    for (int j = 0; j < tests; j++) {
        vector<N> cards(n - 1);

        srand(time(NULL));
        for (int i = 0; i < n - 1; i++) {
            cards[i] = random_T<N>();
        }

        N xor_card = 0;
        for (int i = 0; i < k - 1; i++) xor_card ^= cards[i];
        cards.push_back(xor_card);

        int begin = clock();
        vector<uint8_t> res = merge_results<N, uint8_t>(cards, n, k, split, k / 2);
        times.push_back((clock() - begin) * 1000 / CLOCKS_PER_SEC);

        bool valid = true;
        for (int i = 0; i < k; i++) 
            valid = valid 
                ? (i == k - 1 ? res[i] == n - 1 : res[i] == i)
                : false;

        validity.push_back(valid);
    }

    int valid_count = 0;
    for (bool v: validity) if (v) valid_count += 1;
    cout << valid_count << " valid; " << (tests - valid_count) << " invalid\n";

    int avg = 0;
    for (int t: times) avg += t;
    avg /= tests;

    float std_dev = 0;
    for (int t: times) std_dev += pow(t - avg, 2);
    std_dev /= tests - 1;
    std_dev = sqrt(std_dev);
    cout << "Time: " << avg << " ± " << std_dev << "ms\n";
}