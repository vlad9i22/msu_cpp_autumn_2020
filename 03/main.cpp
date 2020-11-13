#include "Matrix.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>
using namespace std;
size_t count_digit(int a) {
    unsigned count = 0;
    while(a != 0) {
        count++;
        a /= 10;
    }
    return count;
}
class Bigint {
    size_t size;
    int sign;
public:
    char *num;
    Bigint(int a) {
        if(a < 0) {
            sign = -1
        } else {
            sign = 1;
        }
        a *= sign;
        size = count_digit(a) + 1;
        num = new char [size];
        for(size_t i = 0; i < size; ++i) {
            num[i] = a % 10;
            a /= 10;
        }
    }
}
int main() {
    Bigint(15);
    cout << num << endl;
}
