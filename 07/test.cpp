#include <iostream>
#include "Vector.h"
#include <assert.h>
using namespace std;

void Test1() {
    Vector<int> a;
    for(int i = 0; i < 10; ++i) {
        a.push_back(i);
    }
    a[0];
    assert(a[5] == 5);
    assert(a.size() == 10);
    assert(a.capacity() == 16);
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
    assert(a.size() == 3);
    a.pop_back();
    assert(a.size() == 2);
}
void Test4() {
    Vector<int> a;
    a.resize(5);
    assert(a[4] == 0 && a.size() == 5);
    Vector<int> b;
    b.reserve(10);
    for(int i = 0; i < 10; ++i) {
        b.push_back(i);
    }
    assert(b.capacity() == 10);
}

int main() {
    Test1();
    Test2();
    Test3();
    Test4();
    cout << "Program passed tests" << endl;
}
