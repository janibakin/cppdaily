#ifndef RAWBUFFER_H
#define RAWBUFFER_H

#include <cstddef>
#include <cstring>
#include <type_traits>
#include <algorithm>

class RawBuffer {
public:
    // default constructor
    RawBuffer() : size(0), data(nullptr) {}
    // constructor
    explicit RawBuffer(std::size_t bytes) : size(bytes) {
        data = ::operator new(bytes);
    }
    // destructor
    ~RawBuffer() {
        ::operator delete(data);
    }
    // copy constructor
    RawBuffer(const RawBuffer& other) {
        size = other.size;
        data = ::operator new(size);
        std::memcpy(data, other.data, size);
    }
    // copy assignment
    RawBuffer& operator=(const RawBuffer& other) {
        if (this == &other) return *this;
        size = other.size;
        data = ::operator new(size);
        std::memcpy(data, other.data, size);
        return *this;
    }
    // move constructor
    RawBuffer(RawBuffer&& other) noexcept {
        size = other.size;
        data = other.data;
        other.size = 0;
        other.data = nullptr;
    }
    // move assignment
    RawBuffer& operator=(RawBuffer&& other) noexcept {
        if (this == &other) return *this;
        size = other.size;
        data = other.data;
        other.size = 0;
        other.data = nullptr;
        return *this;
    }

private:
    std::size_t size;
    void* data;
};



#endif //RAWBUFFER_H
