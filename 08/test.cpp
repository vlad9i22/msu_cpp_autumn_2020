#include <iostream>
#include "pool.h"
#include <assert.h>
#include <unistd.h>
using namespace std;
int foo(int a) {
    return a + 40;
}

void Test1() {
    ThreadPool pool(8);

    auto task1 = pool.exec(foo, 5);
    auto task2 = pool.exec(foo, 6);
    auto task3 = pool.exec(foo, 7);
    assert(task1.get() == 45 && task2.get() == 46 && task3.get() == 47);
}

struct A {};

void foo1(const A&) {}

void Test2() {
    ThreadPool pool(8);
    auto task1 = pool.exec(foo1, A());
    task1.get();
    auto task2 = pool.exec([]() { return 1; });
    assert(task2.get() == 1);
}
void Test3() {
    ThreadPool pool(8);
    auto task2 = pool.exec([]() { 
        sleep(1);
        return 1; 
    });
}
int main() {
    Test1();
    Test2();
    Test3();
    cout << "Program passed tests" << endl;
}
