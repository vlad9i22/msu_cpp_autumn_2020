#include <iostream>
#include "Allocator.h"
using namespace std;
int main() {
    Allocator a;
    a.makeAllocator(5);
    try {
        if(a.alloc(6) != nullptr) {
            throw "Test 1 not passed";
        }
        char *s = a.alloc(4);
        if(s == nullptr) {
            throw "Test 2 not passed";
        }
        if(a.alloc(2) != nullptr) {
            throw "Test 3 not passed";
        }
        a.reset();
        if(a.alloc(5) == nullptr) {
            throw "Test 4 not passed";
        }
        a.reset();
        a.alloc(5);
        if(a.alloc(1) != nullptr) {
            throw "Test 5 not passed";
        }
        a.reset();
        a.makeAllocator(100);
        cout << "The proggram is running correctly" << endl;
    } catch(const char *s) {
        cout << s << endl;
    }
}