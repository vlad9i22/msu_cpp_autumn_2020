#include <iostream>
#include <functional>
#include <sstream>
#include <string.h>
#include <cassert>
using namespace std;
void StringDefault(std::string s) {
    cout << "I found a string: " << s << endl;
}
void DigitDefault(long long int a) {
    cout << "I found a digit:  " << a << endl;
}
void StartCallDefault() {
    cout << "Started parsing" << endl;
}
void EndCallDefault() {
    cout << "Parsing ended" << endl;
}
bool isDigit(std::string s) {
    for(auto i : s) {
        bool AnyDigits = false;
        for(char num = '0'; num <= '9'; ++num) {
            if(i == num) {
                AnyDigits = true;
            }
        }
        if(!AnyDigits) {
            return false;
        }
    }
    return true;
}
class TokenParser
{
    std::string input;
    std::function<void()> StartCall;
    std::function<void(std::string)> StringCall;
    std::function<void(long long int)> DigitCall;
    std::function<void()> EndCall;
    public:
        TokenParser(std::string s) : StartCall(StartCallDefault), StringCall(StringDefault), 
        DigitCall(DigitDefault),  EndCall(EndCallDefault) {
            for(size_t i = 0; i < s.length(); ++i) {
                if(s[i] == '\t' || s[i] == '\n' || s[i] == '\v') {
                    s[i] = ' ';
                }
            }
            input = s;
        }
        void SetStartCallback(std::function<void()> f) {
            StartCall = f;
        }
        void SetDigitTokenCallback(std::function<void(long long int)> f) {
            DigitCall = f;
        }
        void SetStringTokenCallback(std::function<void(string)> f) {
            StringCall = f;
        }
        void SetEndCallback(std::function<void()> f) {
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