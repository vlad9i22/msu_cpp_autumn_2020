#ifndef TokenParser_H
#define TokenParser_H 
#include <iostream>
#include <functional>
#include <sstream>
#include <string.h>
#include <cassert>
using namespace std;
void StringDefault(const std::string &s) {
    cout << "I found a string: " << s << endl;
}
void DigitDefault(const long long int a) {
    cout << "I found a digit:  " << a << endl;
}
void StartCallDefault() {
    cout << "Started parsing" << endl;
}
void EndCallDefault() {
    cout << "Parsing ended" << endl;
}
bool isDigit(const std::string &s) {
    for(auto &i : s) {
        if(!isdigit(i)) {
            return false;
        }
    }
    return true;
}
class TokenParser
{
    std::string input;
    std::function<void()> StartCall;
    std::function<void(const std::string &)> StringCall;
    std::function<void(const long long int )> DigitCall;
    std::function<void()> EndCall;
    public:
        TokenParser(const std::string &s) : StartCall(StartCallDefault), StringCall(StringDefault), 
        DigitCall(DigitDefault),  EndCall(EndCallDefault) {
            input = s;
            for(size_t i = 0; i < input.length(); ++i) {
                if(input[i] == '\t' || input[i] == '\n' || input[i] == '\v') {
                    input[i] = ' ';
                }
            }
        }
        void SetStartCallback(const std::function<void()> &f) {
            StartCall = f;
        }
        void SetDigitTokenCallback(const std::function<void(const long long int )> &f) {
            DigitCall = f;
        }
        void SetStringTokenCallback(const std::function<void(const std::string &)> &f) {
            StringCall = f;
        }
        void SetEndCallback(const std::function<void()> &f) {
            EndCall = f;
        }
        void Parse() {
            StartCall();
            std::istringstream str(input);
            std::string token;
            while(str >> token) {
                if(isDigit(token)) {
                    long long int digtoken;
                    std::istringstream dig(token);
                    dig >> digtoken;
                    DigitCall(digtoken);
                } else {
                    StringCall(token);
                }
            }
            EndCall();
        }
};
#endif