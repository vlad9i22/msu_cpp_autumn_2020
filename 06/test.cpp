#include <iostream>
#include "format.h"
#include <assert.h>
using namespace std;
class Tester {
    int a;
    int b;
public:
    Tester(int a = 0, int b = 0) : a(a), b(b) {
    }
    friend std::ostream& operator<<(std::ostream &out, const Tester &t);
};


std::ostream &operator<<(std::ostream &out, const Tester &t) {
    out << "first number is " << t.a << " " << "second number is " << t.b;
    return out;
}

void Test1() {
    assert(format("{1}+{1} = {0}", 2, "one") == "one+one = 2");
    assert(format("{3}+{1} = {2}", 1, 2, 3, 4) == "4+2 = 3");
}

void Test2() {
    Tester a(1, 2);
    assert(format("{1}+{1} = {0}", a, "one") == "one+one = first number is 1 second number is 2");
}

void Test3() {
    try {
        format("{1} {2}{3}", 0, 1);
    } catch (const MyOutOfRange &) {
        cout << "Correct catch 1" << endl;
    } catch(...) {
        assert(1 == 0);
    }
    try {
        format("{1} {throw with const!}{3}", 0, 1);
    } catch (const MyInvalidArgument &) {
        cout << "Correct catch 2" << endl;
    } catch(...) {
        assert(1 == 0);
    }
    try {
        format("}{1} {0}{1}", 0, 1);
    } catch (const MyInvalidArgument &) {
        cout << "Correct catch 3" << endl;
    } catch(...) {
        assert(1 == 0);
    }
    try {
        format("{{}}{1} {0}{1}", 0, 1);
    } catch (const MyInvalidArgument &) {
        cout << "Correct catch 4" << endl;
    } catch(...) {
        assert(1 == 0);
    }
    try {
        format("{{}}{1} {0}{1adfgadfghadfgh", "test");
    } catch (const MyInvalidArgument &) {
        cout << "Correct catch 5" << endl;
    } catch(...) {
        assert(1 == 0);
    }
}

int main() {
    Test1();
    Test2();
    Test3();
    cout << "Program passed tests" << endl;
}
