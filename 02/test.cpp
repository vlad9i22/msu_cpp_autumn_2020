#include <iostream>
#include "TokenParser.h"
using namespace std;
long long int glob[3];
std::string test[2];
std::string stringtest[3];
void Functionaltest() {
    TokenParser a("abc hhjk 2 a 25 40");
    a.SetStartCallback([]() {
        test[0] = "hello";
    });
    a.SetEndCallback([]() {
        test[1] = "Goodbye";
    });
    a.SetDigitTokenCallback([](const long long int a) {
        static int i = 0;
        glob[i] = a * a;
        i++;
    });
    a.SetStringTokenCallback([](const std::string &s) {
        static int i = 0;
        stringtest[i] = s;
        i++;
    });
    a.Parse();
    assert(test[0] == "hello");
    assert(test[1] == "Goodbye");
    assert(glob[0] == 4);
    assert(glob[1] == 625);
    assert(glob[2] == 40 * 40);
    assert(stringtest[0] == "abc");
    assert(stringtest[1] == "hhjk");
    assert(stringtest[2] == "a");
}
void SpacesTabsTest() {
    TokenParser a("p[]lklg.jk.gjklabc\t\t\t\n    hhjk     2\n\n\n a \r\r\r25 40");
    a.SetStartCallback([]() {
        test[0] = "hello";
    });
    a.SetEndCallback([]() {
        test[1] = "Goodbye";
    });
    a.SetDigitTokenCallback([](const long long int a) {
        static int i = 0;
        glob[i] = a * a;
        i++;
    });
    a.SetStringTokenCallback([](const std::string &s) {
        static int i = 0;
        stringtest[i] = s;
        i++;
    });
    a.Parse();
    assert(test[0] == "hello");
    assert(test[1] == "Goodbye");
    assert(glob[0] == 4);
    assert(glob[1] == 625);
    assert(glob[2] == 40 * 40);
    assert(stringtest[0] == "p[]lklg.jk.gjklabc");
    assert(stringtest[1] == "hhjk");
    assert(stringtest[2] == "a");
}

int main() {
    Functionaltest();
    SpacesTabsTest();
    cout << "Program is running correctly" << std::endl;
}