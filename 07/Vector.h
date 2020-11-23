#ifndef vector_H
#define vector_H
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <typeinfo>
#include <sstream>
#include <vector>
#include <assert.h>
using namespace std;

template <class T>
class MyAllocator {
public:
    using value_type = T;
    using pointer = T*;
    pointer allocate(size_t n) {
        return new value_type [n];
    }
    void construct(pointer p, const T& value) {
        if(p) {
            *p = value;
        }
    }
    void deallocate(pointer p, size_t) {
        delete [] p;
    }
};


template <class T, class Allocator = MyAllocator<T>>
class Vector {
    size_t size_;
    size_t capacity_;
    Allocator memory;
    T *a;
public:
    using value_type = T;
    Vector(size_t size_ = 0, const T &value = T(), size_t capacity_ = 1): size_(size_), capacity_(capacity_) {
        a = memory.allocate(capacity_);
        for(size_t i = 0; i < size_; ++i) {
            memory.construct(a + i, value);
        }
    }
    T &operator[] (const size_t pos) {
        return a[pos];
    }
    void push_back(const T &value) {
        if(size_ == capacity_) {
            capacity_ *= 2;
            T *b = memory.allocate(capacity_);
            for(size_t i = 0; i < size_; ++i) {
                memory.construct(b + i, *(a + i));
            }
            for(size_t i = size_; i < size_; ++i) {
                memory.construct(b + i, T());
            }
            memory.deallocate(a, capacity_ / 2);
            a = b;
        }
        memory.construct(a + size_, value);
        size_ += 1;
    }
    void pop_back() {
        --size_;
    }
    template<class... Args>
    void emplace_back(Args&&... args) {
        if(size_ == capacity_) {
            capacity_ *= 2;
            T *b = memory.allocate(capacity_);
            for(size_t i = 0; i < size_; ++i) {
                memory.construct(b + i, *(a + i));
            }
            memory.deallocate(a, capacity_ / 2);
            a = b;
        }
        memory.construct(a + size_, T(std::forward<Args>(args)...));
        size_ += 1;
    }
    bool empty() const noexcept {
        return size_ == 0;
    }
    size_t size() const noexcept{
        return this->size_;
    }
    void clear() noexcept{
        size_ = 0;
    }
    class iterator : public std::iterator<std::random_access_iterator_tag, T> {
        T *ptr;
    public:
        iterator(T* ptr) : ptr(ptr) {};
        iterator operator++() {
            iterator i = *this;
            ptr++;
            return i;
        }
        iterator operator++(int a) {
            ptr++;
            return *this;
        }
        T &operator*() {
            return *ptr;
        }
        T *operator->() {
            return ptr;
        }
        bool operator<(const iterator &right) {
            return ptr < right.ptr;
        }
        bool operator==(const iterator &right) {
            return ptr == right.ptr;
        }
        bool operator!=(const iterator &right) {
            return ptr != right.ptr;
        }
    };
    class riterator : public std::iterator<std::random_access_iterator_tag, T> {
        T *ptr;
    public:
        riterator(T* ptr) : ptr(ptr) {};
        riterator operator++() {
            riterator i = *this;
            ptr--;
            return i;
        }
        riterator operator++(int a) {
            ptr--;
            return *this;
        }
        T &operator*() {
            return *ptr;
        }
        T *operator->() {
            return ptr;
        }
        bool operator<(const riterator &right) {
            return ptr > right.ptr;
        }
        bool operator==(const riterator &right) {
            return ptr == right.ptr;
        }
        bool operator!=(const riterator &right) {
            return ptr != right.ptr;
        }
    };
    iterator begin() {
        return iterator(a);
    }
    iterator end() {
        return iterator(a + size_);
    }
    riterator rbegin() {
        if(size_ == 0) {
            return riterator(a);
        }
        return riterator(a + size_ - 1);
    }
    riterator rend() {
        if(size_ == 0) {
            return riterator(a);
        }
        return riterator(a - 1);
    }
    void resize(size_t count) {
        if(count < capacity_) {
            size_ = count;
        } else {
            for(size_t i = size_; i < count; ++i) {
                this->push_back(T());
            }
        }
    }
    void reserve(size_t new_cap) {
        if(new_cap > capacity_) {
            T *b = memory.allocate(new_cap);
            for(size_t i = 0; i < size_; ++i) {
                memory.construct(b + i, *(a + i));
            }
            for(size_t i = size_; i < size_; ++i) {
                memory.construct(b + i, T());
            }
            memory.deallocate(a, capacity_);
            capacity_ = new_cap;
            a = b;
        }
    }
    size_t capacity() const noexcept {
        return capacity_;
    }
    const T& operator[](size_t pos) const{
        cout << "called" << endl;
        return a[pos];
    }
    ~Vector() {
        memory.deallocate(a, capacity_);
    }
};
#endif