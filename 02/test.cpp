#include <iostream>
#include "TokenParser.h"
using namespace std;
void Simpletest() {
    cout << "Simpletest" << std::endl;
    TokenParser a("abcd 34a343345 123123 vbbggfb dfg 333");
    a.Parse();
}
void FunctionTest() {
    cout << std::endl;
    cout << std::endl;
    cout << "FunctionTest" << std::endl;
    TokenParser a("abcd 34a343345 123123 vbbggfb dfg 333 2 3 4 5 5a5");
    a.SetStartCallback([]() {
        cout << "hello" << endl;
    });
    a.SetEndCallback([]() {
        cout << "Goodbye" << endl;
    });
    a.SetDigitTokenCallback([](long long int a) {
        cout << a * a << endl;
    });
    a.SetStringTokenCallback([](std::string s) {
        cout << s << endl;
    });
    a.Parse();
}
void SpacesTabsTest() {
    cout << std::endl;
    cout << std::endl;
    cout << "SpacesTabsTest" << std::endl;
    TokenParser a("a\r\r\r\rbc\t\td\n\n\n\n\n 34a343\n345                 123123 vbbggfb dfg\t\t\t\t\t\t33\n3\n");
    a.Parse();
}

int main() {
    Simpletest();
    FunctionTest();
    SpacesTabsTest();
    cout << "Test completed, check for correctness in console" << std::endl;
}