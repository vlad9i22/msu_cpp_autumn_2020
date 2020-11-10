#ifndef Serializer_H
#define Serializer_H
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
    Error save(T&& object)
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
    Error procces(...) {
        return Error::CorruptedArchive;
    }
    template <typename T, typename... Args>
    Error process(T &&val, Args&&... args) {
        Error wr = process(val);
        if(wr == Error::NoError) {
            out << Separator;
            return process(std::forward<Args>(args)...);
        } else {
            return wr;
        }
    }
    Error process(bool a) {
        if(a) {
            out << "true";
        } else {
            out << "false";
        }
        return Error::NoError;
    }
    Error process(uint64_t &a) {
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
    Error load(T &&object)
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
    Error procces(...) {
        return Error::CorruptedArchive;
    }
    template <typename T, typename... Args>
    Error process(T &&val, Args&&... args) {
        Error wr = process(val);
        if(wr == Error::NoError) {
            return process(std::forward<Args>(args)...);
        } else {
            return wr;
        }
    }
    Error process(bool &a) {
        string s;
        in >> s;
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
        try {
            a = stoull(s);
        } catch(...) {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }
};
#endif