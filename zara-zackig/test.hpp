#include <stdint.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

template<typename T>
T random_T() {
    T num = 0;
    for (int i = 0; i < sizeof (T) / 4; i++) {
        num = (num << 32) | (T) rand();
    }
    return num;
}  