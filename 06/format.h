#ifndef format_H
#define format_H
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <typeinfo>
#include <sstream>
#include <vector>
#include <assert.h>
using namespace std;
void process(std::vector<string> &v) {
    return;
}


template <class T, class ...Args>
void process(std::vector<string> &v, T &&arg, Args &&...args) {
    std::stringstream ss;
    ss << arg;
    v.push_back(ss.str());
    process(v, args...);
}


class MyInvalidArgument : public std::exception
{
    string message;
public:
    MyInvalidArgument(const string &message) : message(message) {}
    ~MyInvalidArgument() = default;
    const char *what() const noexcept {
        return "You argument is invalid";
    }
};


class MyOutOfRange : public std::exception
{
    string message;
public:
    MyOutOfRange(const string &message) : message(message) {}
    ~MyOutOfRange() = default;
    const char *what() const noexcept {
        return "Your argument is out of range";
    }
};


template <class ...Args>
std::string format(const std::string &s, Args &&...args) {
    std::vector<std::string> v;
    process(v, args...);
    std::stringstream res;
    for(size_t i = 0; i < s.size(); ++i) {
        if(s[i] == '}') {
            throw MyInvalidArgument("} without { is a mistake");
        } else if(s[i] != '{') {
            res << s[i];
        } else {
            string num;
            i++;
            while(i < s.size() && s[i] != '}') {
                num += s[i];
                ++i;
            }
            if(s[i] != '}') {
                throw MyInvalidArgument("No } for {");
            }
            size_t number;
            try {
                number = stoull(num);
            } catch(const std::logic_error &) {
                throw MyInvalidArgument("value in {} must be a number");
            }
            try {
                res << v.at(number);
            } catch(const std::out_of_range &) {
                throw MyOutOfRange("Not enough arguments");
            }
        }
    }
    return res.str();
}
#endif