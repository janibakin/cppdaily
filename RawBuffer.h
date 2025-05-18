#ifndef RAWBUFFER_H
#define RAWBUFFER_H

#include <cstddef>
#include <cstring>
#include <type_traits>
#include <utility>
#include <algorithm>

class RawBuffer {
public:
    // default constructor
    RawBuffer() noexcept : sz_(0), data_(nullptr) {}
    // constructor
    explicit RawBuffer(const std::size_t bytes)
        : sz_(bytes)
        , data_(bytes ? ::operator new(bytes) : nullptr) {}
    // destructor
    ~RawBuffer() {
        ::operator delete(data_);
    }
    // copy constructor
    RawBuffer(const RawBuffer& other)
        : sz_(other.sz_)
        , data_(other.sz_ ? ::operator new(other.sz_) : nullptr)
    {
        if (data_)
            std::memcpy(data_, other.data_, sz_);
    }
    // copy assignment
    RawBuffer& operator=(const RawBuffer& other) {
        if (this != &other) {
            void* new_data = other.sz_ ? ::operator new(other.sz_) : nullptr;
            if (new_data && other.data_) {
                std::memcpy(new_data, other.data_, other.sz_);
            }
            ::operator delete(data_);
            data_ = new_data;
            sz_ = other.sz_;
        }
        return *this;
    }
    // move constructor
    RawBuffer(RawBuffer&& other) noexcept
        : sz_(std::exchange(other.sz_, 0))
        , data_(std::exchange(other.data_, nullptr))
    {}
    // move assignment
    RawBuffer& operator=(RawBuffer&& other) noexcept {
        if (this != &other) {
            ::operator delete(data_);
            sz_ = std::exchange(other.sz_, 0);
            data_ = std::exchange(other.data_, nullptr);
        }
        return *this;
    }
    [[nodiscard]] std::size_t size() const noexcept { return sz_; }
    [[nodiscard]] std::byte* data() const noexcept { return static_cast<std::byte*>(data_);}

private:
    std::size_t sz_;
    void* data_;
};



#endif //RAWBUFFER_H
