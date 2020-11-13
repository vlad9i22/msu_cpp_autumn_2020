#include <iostream>
#include "Matrix.h"
using namespace std;
void GetTest() {
    Matrix a(500, 40);
    assert(a.getRows() == 500);
    assert(a.getColumns() == 40);
}
void ElementTest() {
    Matrix a(3, 3);
    a[0][1] = 4;
    a[2][2] = 7;
    assert(a[0][1] == 4);
    assert(a[2][2] == 7);
}
void OutOfRangeTest() {
    Matrix a(3, 6);
    try {
        a[67][2];
    } catch(const std::out_of_range &a) {
        cout << "OutOfRows is correct" << endl;
    } 
    catch(...) {
        throw "Wrong out of range test";
    }
    try {
        a[2][3535];
    } catch(const std::out_of_range &a) {
        cout << "OutOfColumns is correct" << endl;
    } 
    catch(...) {
        throw "Wrong out of range test";
    }
}
void EqualTest() {
    Matrix a(2, 2);
    Matrix b(2, 2);
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < 2; ++j) {
            a[i][j] = (i + 1) * (j + 1);
            b[i][j] = (i + 1) * (j + 1);
        }
    }
    assert((a == b) == true);
    b[0][0] = 300;
    assert((a == b) == false);
    assert((a != b) == true);
}
void AddTest() {
    Matrix a(2, 2);
    Matrix b(2, 2);
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < 2; ++j) {
            a[i][j] = (i + 1) * (j + 1);
        }
    }
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < 2; ++j) {
            b[i][j] = 1;
        }
    }
    a = a + b;
    assert(a[0][0] == 2);
    assert(a[0][1] == 3);
    assert(a[1][0] == 3);
    assert(a[1][1] == 5);
    a = a + a + a + b;
    assert(a[0][0] == 7);
    assert(a[0][1] == 10);
    assert(a[1][0] == 10);
    assert(a[1][1] == 16);
}
void MultTest() {
    Matrix a(2, 2);
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < 2; ++j) {
            a[i][j] = 2 + i;
        }
    }
    a *= 3;
    assert((a[0][0] == 6));
    assert((a[0][1] == 6));
    assert(a[1][0] == 9);
    assert(a[1][1] == 9);
}
int main() {
    GetTest();
    ElementTest();
    OutOfRangeTest();
    EqualTest();
    AddTest();
    MultTest();
    cout << "Program is running correctly" << std::endl;
}