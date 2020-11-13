#include <iostream>
using namespace std;
class Allocator
{
    char *p;
    size_t size;
    size_t offset;
public:
    Allocator(): p(nullptr), size(0), offset(0){
    }
    void makeAllocator(size_t maxSize) {
        if(maxSize == 0) {
            return;
        }
        if(p != nullptr) {
            cout << "Memory is already allocated" << endl;
            return;
        }
        p = new char [maxSize];
        if(p == nullptr) {
            cout << "Allocation failed" << endl;
            exit(404);
        }
        size = maxSize;
    }
    char* alloc(size_t size) {
        if(this->size - offset < size) {
            return nullptr;
        }
        size_t save = offset;
        offset += size;
        return p + save;
    }
    void reset() {
        offset = 0;
    }
    ~Allocator() {
        if(p != nullptr) {
            delete [] p;
        }
    }
};
