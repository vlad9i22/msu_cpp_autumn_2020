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
template <class T, class Allocator = std::allocator<T>>
class Vector {
    size_t size;
    size_t capacity;
    Allocator memory;
    T *a;
public:
    using value_type = T;
    Vector(size_t size = 0, const T &value = T(), size_t capacity = 1): size(size), capacity(capacity) {
        a = memory.allocate(capacity);
        for(size_t i = 0; i < size; ++i) {
            memory.construct(a + i, value);
        }
    }
    T &operator[] (const size_t pos) {
        return a[pos];
    }
    void push_back(const T &value) {
        if(size == capacity) {
            capacity *= 2;
            T *b = memory.allocate(capacity);
            for(size_t i = 0; i < size; ++i) {
                memory.construct(b + i, *(a + i));
            }
            for(size_t i = size; i < size; ++i) {
                memory.construct(b + i, T());
            }
            memory.deallocate(a, capacity / 2);
            a = b;
        }
        memory.construct(a + size, value);
        size += 1;
    }
    T pop_back() {
        return a[--size];
    }
    template<class... Args>
    void emplace_back(Args&&... args) {
        if(size == capacity) {
            capacity *= 2;
            T *b = memory.allocate(capacity);
            for(size_t i = 0; i < size; ++i) {
                memory.construct(b + i, *(a + i));
            }
            memory.deallocate(a, capacity / 2);
            a = b;
        }
        memory.construct(a + size, T(std::forward<Args>(args)...));
        size += 1;
    }
    bool empty() const noexcept {
        return size == 0;
    }
    size_t my_size() const noexcept{
        return this->size;
    }
    void clear() noexcept{
        size = 0;
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
        return iterator(a + size);
    }
    riterator rbegin() {
        if(size == 0) {
            return riterator(a);
        }
        return riterator(a + size - 1);
    }
    riterator rend() {
        if(size == 0) {
            return riterator(a);
        }
        return riterator(a - 1);
    }
    void resize(size_t count) {
        if(count < capacity) {
            size = count;
        } else {
            for(size_t i = size; i < count; ++i) {
                this->push_back(T());
            }
        }
    }
    void reserve(size_t new_cap) {
        if(new_cap > capacity) {
            T *b = memory.allocate(new_cap);
            for(size_t i = 0; i < size; ++i) {
                memory.construct(b + i, *(a + i));
            }
            for(size_t i = size; i < size; ++i) {
                memory.construct(b + i, T());
            }
            memory.deallocate(a, capacity);
            capacity = new_cap;
            a = b;
        }
    }
    size_t my_capacity() const noexcept {
        return capacity;
    }
    ~Vector() {
        memory.deallocate(a, capacity);
    }
};
#endif