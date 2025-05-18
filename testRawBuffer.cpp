#include "RawBuffer.h"
#include <cassert>

int main() {
    RawBuffer buf1(1024);
    RawBuffer buf2;
    buf2 = buf1; // copy assignment
    RawBuffer buf3(buf2); // copy
    RawBuffer buf4;
    buf4 = std::move(buf1); // move assignment
    RawBuffer buf5(std::move(buf3)); // move


    RawBuffer b1(4);
    std::byte pattern[4]{std::byte{0xAA}, std::byte{0xBB},
                         std::byte{0xCC}, std::byte{0xDD}};
    std::memcpy(b1.data(), pattern, 4);

    RawBuffer b2 = b1;           // deep copy
    assert(std::memcmp(b1.data(), b2.data(), 4) == 0);

    RawBuffer b3 = std::move(b1); // move
    assert(b1.data() == nullptr); // source cleared
    assert(std::memcmp(b2.data(), b3.data(), 4) == 0);

    return 0;
}