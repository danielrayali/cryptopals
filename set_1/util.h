#pragma once

#include <vector>
#include <cstdint>

// Returns a slice of the input. If the requested end is beyond the size of the input, only the data that
// can be returned is.
std::vector<uint8_t> Slice(const std::vector<uint8_t>& input, const size_t index, const size_t size) {
    std::vector<uint8_t> output;
    for (size_t i = 0; i < size; ++i) {
        if ((index + i) >= input.size()) {
            break;
        }
        output.push_back(input.at(index + i));
    }
    return output;
}
