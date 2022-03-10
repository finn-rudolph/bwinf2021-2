#include <iostream>
#include "k_xor.hpp"
using namespace std;

int main() {
    int n, k, m;
    cin >> n >> k >> m;
    k += 1;
    
    switch (m) {
        case 8: {
            decide_parameters<uint8_t>(n, k, m);
            break;
        }
        case 16: {
            decide_parameters<uint16_t>(n, k, m);
            break;
        }
        case 32: {
            decide_parameters<uint32_t>(n, k, m);
            break;
        }
        case 64: {
            decide_parameters<uint64_t>(n, k, m);
            break;
        }
        case 128: {
            decide_parameters<__uint128_t>(n, k, m);
            break;
        }
    }
}
