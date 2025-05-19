#include "CompactBitset.h"
#include "common.h"

int main() {
    CompactBitset bits(16); // bitset with 16 bits: all initially 0

    bits.set(3);            // Set bit 3 to 1
    bits.set(7);            // Set bit 7 to 1
    bits.set(15);           // Set bit 15 to 1

    assert(bits.test(3) == true);     // bit 3 is set
    assert(bits.test(2) == false);    // bit 2 is not set
    assert(bits.test(15) == true);    // last bit is set

    bits.clear(3);         // Clear bit 3
    assert(bits.test(3) == false);    // bit 3 now unset

    std::cout << "Bit 7: " << bits.test(7) << "\n";
    std::cout << "Bit 15: " << bits.test(15) << "\n";
    std::cout << "Size: " << bits.size() << "\n";  // Should print 16

    CompactBitset bits24(24);
    bits24.set(23);
    bits24.set(5);
    bits24.set(4);
    bits24.set(12);
    bits24.set(20);
    bits24.clear(20);
    bits24.clear(0);

    assert(bits24.count() == 4);
}
