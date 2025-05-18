#include "RawBuffer.h"

int main() {
    RawBuffer buf1(1024);
    RawBuffer buf2;
    buf2 = buf1; // copy assignment
    RawBuffer buf3(buf2); // copy
    RawBuffer buf4;
    buf4 = std::move(buf1); // move assignment
    RawBuffer buf5(std::move(buf3)); // move
    return 0;
}