#ifndef Matrix_H
#define Matrix_H 
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <string>
using namespace std;
int64_t count_digit(int a) {
    unsigned count = 0;
    while(a != 0) {
        count++;
        a /= 10;
    }
    return count;
}
class myvector {
    char *num;
    int size;
    int curr;
public:
    myvector(int64_t size = 10): size(size), curr(0) {
        num = new char [size];
    }
    myvector(const myvector& a): size(a.size), curr(a.curr) {
        num = new char[size];
        for(int64_t i = 0; i < size; ++i) {
            num[i] = a[i];
        }
    }
    myvector(myvector &&str) : num(str.num), size(str.size), curr(str.curr) {
      str.num = nullptr;
      str.size = 0;
      str.curr = 0;
    }
    myvector &operator=(const myvector &a) {
        if(this == &a) {
            return *this;
        }
        num = new char [a.size];
        for(int64_t i = 0; i < a.size; ++i) {
            num[i] = a.num[i];
        }
        size = a.size;
        curr = a.curr;
        return *this;
    }
    void deletezeros() {
        while(curr - 1 > 0 && num[curr - 1] == 0) {
            curr--;
        }
    }
    char &operator[](const int64_t index) const {
        return num[index];
    }
    void push_back(char a) {
        if(curr == size) {
            char *n_num = new char [size * 2];
            for(int64_t i = 0; i < size; ++i) {
                n_num[i] = num[i];
            }
            delete [] num;
            num = n_num;
            size = size * 2;
        }
        num[curr] = a;
        curr++;
    }
    int64_t mysize() const {
        return curr;
    }
    ~myvector() {
        delete [] num;
    }
};
class Bigint {
    int sign;
    myvector num;
public:
    Bigint(): num() {
        sign = 1;
    }
    Bigint(int a) {
        if(a == 0) {
            num.push_back(0);
        }
        if(a < 0) {
            sign = -1;
        } else {
            sign = 1;
        }
        a *= sign;
        while(a > 0) {
            num.push_back(a % 10);
            a /= 10;
        }
    }
    Bigint(std::string s) {
        if(s[0] == '-') {
            sign = -1;
        } else {
            sign = 1;
        }
        for(int64_t i = s.size() - 1; i >= 0; --i) {
            if(s[i] != '-') {
                num.push_back(s[i] - '0');
            }
        }
    }
    Bigint(Bigint &&str) : sign(str.sign), num(str.num) {
      str.num = myvector(0);
      str.sign = 1;
    }
    Bigint(const Bigint& a) = default;
    char &operator[](const int64_t i) const{
        return num[i];
    }
    Bigint &operator=(const Bigint &a) {
        if(this == &a) {
            return *this;
        }
        num = a.num;
        sign = a.sign;
        return *this;
    }
    const Bigint operator-() const {
        Bigint copy;
        for(int64_t i = 0; i < num.mysize(); ++i) {
            copy.num.push_back(num[i]);
        }
        copy.sign = (sign == -1 ? 1 : -1);
        return copy;
    }
    friend Bigint operator+ (const Bigint &ro, const Bigint &lf);
    friend std::ostream& operator<<(std::ostream& os, const Bigint& a);
    friend bool operator ==(const Bigint& lf, const Bigint& ro);
    friend bool operator <(const Bigint& lf, const Bigint& ro);
    friend bool operator >(const Bigint& lf, const Bigint& ro);
    friend Bigint operator-(const Bigint &lf, const Bigint &ro);
    friend Bigint operator*(const Bigint &lf, const Bigint &ro);
};
bool operator ==(const Bigint& lf, const Bigint& ro) {
    if(lf.sign != ro.sign) {
        return false;
    }
    if(lf.num.mysize() > ro.num.mysize()) {
        return false;
    } else if (ro.num.mysize() > lf.num.mysize()) {
        return false;
    }
    for(int64_t i = 0; i < lf.num.mysize(); ++i) {
        if(lf.num[i] != ro.num[i]) {
            return false;
        }
    }
    return true;
}
bool operator <(const Bigint& lf, const Bigint& ro) {
    if(lf.sign != ro.sign) {
        return lf.sign < ro.sign;
    }
    if(lf.num.mysize() > ro.num.mysize()) {
        return false;
    } else if (ro.num.mysize() > lf.num.mysize()) {
        return true;
    }
    if(lf == ro) {
        return 0;
    }
    for(int64_t i = lf.num.mysize(); i >= 0; --i) {
        if(lf.num[i] > ro.num[i]) {
            return false;
        }
    }
    return true;
}
bool operator >(const Bigint& lf, const Bigint& ro) {
    if(lf.sign != ro.sign) {
        return lf.sign > ro.sign;
    }
    if(lf == ro) {
        return false;
    }
    if(lf.num.mysize() < ro.num.mysize()) {
        return false;
    } else if (ro.num.mysize() < lf.num.mysize()) {
        return true;
    }
    for(int64_t i = lf.num.mysize(); i >= 0; --i) {
        if(lf.num[i] < ro.num[i]) {
            return false;
        }
    }
    return true;
}
bool operator !=(const Bigint& lf, const Bigint& ro) {
        return !(lf == ro);
}
bool operator <=(const Bigint& lf, const Bigint& ro) {
        return (lf < ro || lf == ro);
} 
bool operator >=(const Bigint& lf, const Bigint& ro) {
        return !(lf < ro);
}
Bigint operator-(const Bigint &lf1, const Bigint &ro1) {
    if(lf1 == -ro1) {
        return Bigint(0);
    }
    if(lf1.sign == -1 && ro1.sign == -1) {
        return -((-lf1) - (-ro1));
    }
    if(lf1.sign == 1 && ro1.sign == -1) {
        return (lf1 + -ro1);
    }
    if(lf1.sign == -1 && ro1.sign == 1) {
        return -(-lf1 + ro1);
    }
    Bigint res;
    Bigint lf = lf1, ro = ro1;
    if(lf < ro) {
        lf = ro1;
        ro = lf1;
        res.sign = -1;
    }
    int64_t size = max(lf.num.mysize(), ro.num.mysize());
    int carry = 0;
    for(int i = 0; i < size || carry != 0; ++i) {
        char l, r;
        l = i >= lf.num.mysize() ? 0 : lf[i];
        r = i >= ro.num.mysize() ? 0 : ro[i];
        res.num.push_back(l - r - carry);
        carry = (l - r - carry) < 0;
        if(carry != 0) {
            res[i] += 10;
        }
    }
    res.num.deletezeros();
    return res;
}
Bigint operator+(const Bigint &lf, const Bigint &ro) {
    if(lf.sign == -1 && ro.sign == -1) {
        return -(-ro + -lf);
    }
    if(lf.sign == 1 && ro.sign == -1) {
        return lf - (-ro);
    }
    if(lf.sign == -1 && ro.sign == 1) {
        return ro - (- lf);
    }
    Bigint res;
    int64_t size = max(lf.num.mysize(), ro.num.mysize());
    char add = 0;
    for(int i = 0; i < size || add != 0; ++i) {
        char l = i >= lf.num.mysize() ? 0 : lf[i];
        char r = i >= ro.num.mysize() ? 0 : ro[i];
        res.num.push_back((l + r + add) % 10);
        add = (l + r + add) / 10;
    }
    res.num.deletezeros();
    return res;
}
Bigint operator*(const Bigint &lf, const Bigint &ro) {
    if(lf == 0 || ro == 0) {
        return Bigint(0);
    }
    Bigint res = ro;
    res.sign = 1;
    Bigint count = lf - 1;
    count.sign = 1;
    while(count != 0) {
        count = count - 1;
        res = res + ro;
    }
    res.sign = lf.sign * ro.sign;
    res.num.deletezeros();
    return res;
}


std::ostream& operator<<(std::ostream& os, const Bigint& a)
{
    if(a.sign == -1) {
        os << "-";
    }
    int i = a.num.mysize() - 1;
    for(; i >= 0; --i) {
        os << int(a.num[i]);
    }
    os << endl;
    return os;
}
#endif