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
template <class ...Args>
std::string format(const std::string &s, Args &&...args) {
    std::vector<std::string> v;
    process(v, args...);
    std::stringstream res;
    for(size_t i = 0; i < s.size(); ++i) {
        if(s[i] == '}') {
            throw std::invalid_argument("} without { is a mistake");
        } else if(s[i] != '{') {
            res << s[i];
        } else {
            string num;
            i++;
            while(i < s.size() && s[i] != '}') {
                num += s[i];
                ++i;
            }
            size_t number;
            try {
                number = stoull(num);
            } catch(const std::logic_error &) {
                throw std::invalid_argument("value in {} must be a number");
            }
            try {
                res << v.at(number);
            } catch(const std::out_of_range &) {
                throw std::out_of_range("Not enough arguments");
            }
        }
    }
    return res.str();
}
#endif