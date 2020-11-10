#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <typeinfo>
#include <sstream>
#include <assert.h>
using namespace std;
enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out) : out(out) {
    }

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT... args)
    {
        return process(args...);
    }
private:
    std::ostream &out;
    template <typename T>
    Error procces(T) {
        return Error::CorruptedArchive;
    }
    template <typename T, typename... Args>
    Error process(T &&val, Args&&... args) {
        Error wr = process(val);
        if(wr == Error::NoError) {
            out << Separator;
            return process(args...);
        } else {
            return wr;
        }
    }
    Error process(bool &a) {
        cout << "bool" << a << endl;
        if(a) {
            out << "true";
        } else {
            out << "false";
        }
        return Error::NoError;
    }
    Error process(uint64_t &a) {
        cout << "int" << a << endl;
        out << a;
        return Error::NoError;
    }
};
class Deserializer
{
    static constexpr char Separator = ' ';
public:
    explicit Deserializer(std::istream& in) : in(in) {
    }

    template <class T>
    Error load(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args)
    {
        return process(args...);
    }
private:
    std::istream &in;
    template <typename T>
    Error procces(T&&) {
        return Error::CorruptedArchive;
    }
    template <typename T, typename... Args>
    Error process(T &&val, Args&&... args) {
        Error wr = process(val);
        if(wr == Error::NoError) {
            return process(args...);
        } else {
            return wr;
        }
    }
    Error process(bool &a) {
        string s;
        in >> s;
        cout << s << endl;
        if(s == "true") {
            a = true;
        } else if(s == "false") {
            a = false;
        } else {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }
    Error process(uint64_t &a) {
        string s;
        in >> s;
        cout << s << endl;
        try {
            a = stoull(s);
        } catch(...) {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }
};
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

int main() {
    Data x { 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data y { 0, false, 0 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);
    cout << y.a << endl;
    assert(err == Error::NoError);

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
}