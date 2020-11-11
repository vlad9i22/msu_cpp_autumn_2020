#include <iostream>
#include "Serializer.h"
#include <assert.h>
using namespace std;
struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
};
struct Data1
{
    uint64_t a;
    bool b;
    bool c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
};
struct Data2
{
    string c;
    uint64_t a;
    bool b;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
};

void Test1() {
    Data x { 1, true, 2 };
    std::stringstream stream;
    Serializer serializer(stream);
    serializer.save(x);
    Data y { 0, false, 0 };
    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);
    assert(err == Error::NoError);
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
}
void Test2() {
    Data x { 1, true, 223 };
    std::stringstream stream;
    Serializer serializer(stream);
    serializer.save(x);
    Data1 y { 0, false, 0 };
    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);
    assert(err == Error::CorruptedArchive);
}
// void Test3() {
//     Data2 x { "abcdffe", 234, true };
//     std::stringstream stream;
//     Serializer serializer(stream);
//     serializer.save(x);
// }
int main() {
    Test1();
    Test2();
    cout << "Program passed tests" << endl;
}