//
// Created by Zhanibek Bakin on 19.05.2025.
//

#ifndef COMPACTBITSET_H
#define COMPACTBITSET_H

#include <cstddef>
#include <cstdint>

class CompactBitset {
public:
    explicit CompactBitset(const std::size_t numBits)
        : numBits_(numBits),
          bits_(new uint8_t[(numBits_ + 7) / 8])
    {}
    ~CompactBitset() {
        delete[] bits_;
    }
    CompactBitset(const CompactBitset&) = delete;
    CompactBitset& operator=(const CompactBitset&) = delete;
    CompactBitset(CompactBitset&&) = delete;
    CompactBitset& operator=(CompactBitset&&) = delete;

    void set(const std::size_t index) {
        bits_[index / 8] |= static_cast<uint8_t>(1u << index % 8);
    }
    void clear(const std::size_t index) {
        bits_[index / 8] &= static_cast<uint8_t>(~(1u << index % 8));
    }
    [[nodiscard]] bool test(const std::size_t index) const {
        return bits_[index / 8] & (1 << index % 8);
    }
    [[nodiscard]] std::size_t size() const noexcept {
        return numBits_;
    }
    [[nodiscard]] std::size_t count() const noexcept {
        std::size_t count {};
        const std::size_t fullBytes = numBits_ / 8;
        const std::size_t remainder = numBits_ % 8;
        for (std::size_t i = 0; i < fullBytes; ++i) {
            count += __builtin_popcount(bits_[i]);
        }
        if (remainder) {
            const uint8_t mask = (1u << remainder) - 1;
            count += __builtin_popcount(bits_[fullBytes] & mask);
        }
        return count;
    }
private:
    std::size_t numBits_;
    std::uint8_t* bits_{};  // raw byte array
};


#endif //COMPACTBITSET_H
