#include <iostream>
#include "Vector.h"
#include <assert.h>
using namespace std;

void Test1() {
    Vector<int> a;
    for(int i = 0; i < 10; ++i) {
        a.push_back(i);
    }
    assert(a[5] == 5);
    assert(a.my_size() == 10);
    assert(a.my_capacity() == 16);
}

void Test2() {
    Vector<int> a;
    for(int i = 0; i < 10; ++i) {
        a.emplace_back(i);
    }
    int k = 0;
    for(auto i = a.begin(); i < a.end(); ++i) {
        assert(*i == k);
        k++;
    }
    k = 9;
    for(auto i = a.rbegin(); i < a.rend(); ++i) {
        assert(*i == k);
        k--;
    }
    a.clear();
    assert(a.empty() == true);
}

void Test3() {
    Vector<double> a;
    assert(a.empty() == true);
    a.push_back(3);
    a.push_back(4);
    a.push_back(5);
    assert(a.my_size() == 3);
    double b = a.pop_back();
    assert(b == 5 && a.my_size() == 2);
}
void Test4() {
    Vector<int> a;
    a.resize(5);
    assert(a[4] == 0 && a.my_size() == 5);
    Vector<int> b;
    b.reserve(10);
    for(int i = 0; i < 10; ++i) {
        b.push_back(i);
    }
    assert(b.my_capacity() == 10);
}

int main() {
    Test1();
    Test2();
    Test3();
    Test4();
    cout << "Program passed tests" << endl;
}
