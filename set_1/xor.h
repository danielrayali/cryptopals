#pragma once

#include <vector>
#include <algorithm>
#include <cstdint>

std::vector<uint8_t> XorEqual(const std::vector<uint8_t>& left, const std::vector<uint8_t>& right) {
    size_t size = std::min(left.size(), right.size());
    std::vector<uint8_t> output(size, 0);
    for (size_t i = 0; i < size; ++i) {
        output[i] = left[i] ^ right[i];
    }
    return output;
}

std::vector<uint8_t> XorSingle(const std::vector<uint8_t>& input, const uint8_t key) {
    std::vector<uint8_t> output(input.size(), 0);
    for (size_t i = 0; i < input.size(); ++i) {
        output[i] = input[i] ^ key;
    }
    return output;
}

std::vector<uint8_t> XorRepeat(const std::vector<uint8_t>& longer, const std::vector<uint8_t>& shorter) {
    size_t size = longer.size();
    size_t shorter_idx = 0;
    std::vector<uint8_t> output(size, 0);
    for (size_t i = 0; i < size; ++i) {
        output[i] = longer[i] ^ shorter[shorter_idx];
        shorter_idx = (shorter_idx + 1) % shorter.size();
    }
    return output;
}
