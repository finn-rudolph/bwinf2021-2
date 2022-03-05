#include <bits/stdc++.h>
#include "k_xor.hpp"
using namespace std;

int main() {
    int n, k, m;
    cin >> n >> k >> m;
    k += 1;
    
    switch (m) {
        case 8: {
            find_k_xor<uint8_t>(n, k);
            break;
        }
        case 16: {
            find_k_xor<uint16_t>(n, k);
            break;
        }
        case 32: {
            find_k_xor<uint32_t>(n, k);
            break;
        }
        case 64: {
            find_k_xor<uint64_t>(n, k);
            break;
        }
        case 128: {
            find_k_xor<__uint128_t>(n, k);
            break;
        }
    }
}
