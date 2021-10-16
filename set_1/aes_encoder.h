#pragma once

#include <cstdint>
#include <vector>

class AesEncoder {
public:
    AesEncoder() = default;

    ~AesEncoder() = default;

    std::vector<uint8_t> Encode(const std::vector<uint8_t>&) {
        return {};
    }

    std::vector<uint8_t> Decode(const std::vector<uint8_t>&) {
        return {};
    }
};
