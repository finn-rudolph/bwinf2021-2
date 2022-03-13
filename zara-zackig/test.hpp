#include <stdint.h>
#include <cstdlib>
#include <ctime>
using namespace std;

template<typename T>
T random_T() {
    if (sizeof (T) <= 4) return rand();
    T num = 0;
    for (int i = 0; i < sizeof (T) / 4; i++) {
        num = (num << 32) | (T) rand(); //
    }
    return num;
}  