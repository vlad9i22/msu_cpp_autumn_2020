#ifndef Bigint_H
#define Bigint_H 
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <iomanip>
using namespace std;
class Bigint {
    bool sign = 0;
    size_t size = 0;
    int *array = nullptr;
    size_t buf = 0;
    const size_t cap_step = 4;
    const int base = 1000;
    const int nbase = 3;
public:
    Bigint(){}
    Bigint(int a) {
        sign =  (a < 0);
        a = std::abs(a);
        array = new int[cap_step]();
        buf = cap_step;
        do {
            if(size == buf) {
                buf += cap_step;
                int *tmp = new int[buf]();
                std::copy(array, array + size, tmp);
                delete [] array;
                array = tmp;
            }
            array[size++] = a % base;
            a /= base;
        } while(a > 0);
    }
    Bigint(const std::string &s) {
        int str_size = s.size();
        if(str_size <= 0) {
            return;
        }
        sign = (s[0] == '-');
        size = (str_size + nbase - 1) / nbase;
        buf = size + cap_step - 1;
        array = new int [buf]();
        int start = !isdigit(s[0]);
        int i = max(start, str_size + start - nbase);
        int j = 0;
        do {
            const char *tmp = s.substr(i, nbase).c_str();
            array[j++] = atoi(tmp);
            i -= nbase;
        } while(start <= i);
        if(i + nbase > start) {
            const char *tmp = s.substr(start, nbase + i - start).c_str();
            array[j++] = atoi(tmp);
        }
    }
    Bigint(const Bigint &a) {
        sign = a.sign;
        buf = a.buf;
        size = a.size;
        array = new int [buf]();
        std::copy(a.array, a.array + size, array);
    }
    Bigint(Bigint &&a) {
        sign = a.sign;
        buf = a.buf;
        size = a.size;
        array = a.array;
        a.array = nullptr;
    }
    Bigint &operator=(const Bigint &a) {
        if(this == &a) {
            return *this;
        }
        size = a.size;
        buf =  a.buf;
        sign = a.sign;
        int *tmp = new int [buf]();
        std::copy(a.array, a.array + size, tmp);
        delete [] array;
        array = tmp;
        return *this;
    }
    Bigint &operator=(Bigint &&a) {
        if(this == &a) {
            return *this;
        }
        size = a.size;
        buf =  a.buf;
        sign = a.sign;
        array = a.array;
        a.array = nullptr;
        return *this;
    }
    const Bigint operator-() const {
        Bigint res = *this;
        res.sign = !sign;
        return res;
    }
    friend Bigint operator+ (const Bigint &lf, const Bigint &ro);
    friend std::ostream& operator<<(std::ostream& os, const Bigint& a);
    friend bool operator ==(const Bigint& lf, const Bigint& ro);
    friend bool operator !=(const Bigint& lf, const Bigint& ro);
    friend bool operator <(const Bigint& lf, const Bigint& ro);
    friend bool operator >(const Bigint& lf, const Bigint& ro);
    friend bool operator <=(const Bigint& lf, const Bigint& ro);
    friend bool operator >=(const Bigint& lf, const Bigint& ro);
    friend Bigint operator-(const Bigint &lf, const Bigint &ro);
    friend Bigint operator*(const Bigint &lf, const Bigint &ro);
    friend Bigint Sum(const Bigint &a, const Bigint &b);
    friend Bigint Diff(const Bigint &a, const Bigint &b);
    ~Bigint() {
        delete [] array;
    }
};
bool operator <(const Bigint& lf, const Bigint& ro) {
    if(lf.sign != ro.sign) {
        return lf.sign;
    }
    if(lf.size != ro.size) {
        return (lf.size > ro.size) == lf.sign;
    }
    for(int i = 0; i >= 0; --i) {
        if(lf.array[i] != ro.array[i]) {
            return (lf.array[i] > ro.array[i]) == lf.sign;
        }
    }
    return false;
}
bool operator <=(const Bigint& lf, const Bigint& ro) {
    return lf < ro || lf == ro;
}
bool operator >(const Bigint& lf, const Bigint& ro) {
    return !(lf <= ro);
}
bool operator >=(const Bigint& lf, const Bigint& ro) {
    return lf > ro || lf == ro;
}
bool operator !=(const Bigint& lf, const Bigint& ro) {
    return !(lf == ro);
}
Bigint operator+ (const Bigint &lf, const Bigint &ro) {
    if(ro.sign != lf.sign) {
        if(lf.sign) {
            return Diff(ro, -lf);
        } else {
            return Diff(lf, -ro);
        }
    }
    return Sum(lf, ro);
}
Bigint operator-(const Bigint &lf, const Bigint &ro) {
    if(lf.sign != ro.sign) {
        return Sum(lf, ro);
    }
    if(lf.sign) {
        return Diff(-ro, -lf);
    }
    return Diff(lf, ro);
}
Bigint operator*(const Bigint &lf, const Bigint &ro) {
    Bigint res;
    res.sign = (lf.sign != ro.sign);
    res.buf = lf.size + ro.size + lf.cap_step;
    res.array = new int [res.buf]();
    size_t j = 0;
    while(j < ro.size) {
        size_t i = 0;
        int carry = 0;
        for(;i < lf.size; ++i) {
            res.array[i + j] += ro.array[j] * lf.array[i] + carry;
            carry = res.array[i + j] / lf.base;
            res.array[i + j] %= lf.base;
        }
        while(carry) {
            res.array[i + j] += carry;
            carry = res.array[i + j] / lf.base;
            res.array[i + j] %= lf.base;
            ++i;
        }
        ++j;
    }  
    int find_size = res.buf;
    for(; res.array[find_size - 1] == 0 && find_size > 1; --find_size);
    res.size = find_size;
    return res;
}
std::ostream& operator<<(std::ostream& out, const Bigint& a) {
    if(a.size == 0) {
        return out;
    }
    if(a.sign) {
        out << '-';
    }
    out << a.array[a.size - 1];
    for(int i = a.size - 2; i >= 0; --i) {
        out << std::setfill('0') << std::setw(a.nbase) << a.array[i];
    }
    return out;
}
bool operator ==(const Bigint& lf, const Bigint& ro) {
    if(lf.size != ro.size || lf.sign != ro.sign) {
        return false;
    }
    for(size_t i = 0; i < lf.size; ++i) {
        if(lf.array[i] != ro.array[i]) {
            return false;
        }
    }
    return true;
}
Bigint Sum(const Bigint &a, const Bigint &b) {
    Bigint res;
    res.sign = a.sign;
    res.buf = max(a.buf, b.buf) + res.cap_step;
    res.array = new int [res.buf]();
    std::copy(a.array, a.array + a.size, res.array);
    size_t i = 0;
    int carry = 0;
    for(; i < b.size; ++i) {
        res.array[i] += b.array[i] + carry;
        carry = res.array[i] / res.base;
        res.array[i] %= res.base;
    }
    while(carry) {
        res.array[i] += carry;
        carry = res.array[i] / res.base;
        res.array[i] %= res.base;
        ++i;
    }
    res.size = max(i, res.size);
    return res;
}
Bigint Diff(const Bigint &a, const Bigint &b) {
    Bigint res;
    if(b > a) {
        res = Diff(b, a);
        res.sign = 1;
        return res;
    }
    res = a;
    size_t i = 0;
    while(i < b.size) {
        res.array[i] -= b.array[i];
        if(res.array[i] < 0) {
            res.array[i + 1] -= 1;
            res.array[i] += res.base;
        }
        ++i;
    }
    while((i < res.size - 1) && res.array[i] < 0) {
        res.array[i + 1] -= 1;
        res.array[i] += res.base;
        ++i;
    }
    while(res.array[res.size - 1] == 0 && res.size > 1) {
        res.size--;
    }
    return res;
}
#endif