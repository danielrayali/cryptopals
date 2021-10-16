#pragma once

#include <vector>
#include <cstdint>

// Returns a slice of the input. If the requested end is beyond the size of the input, only the data that
// can be returned is.
std::vector<uint8_t> Slice(const std::vector<uint8_t>& input, const size_t index, size_t size) {
    std::vector<uint8_t> output;
    if (size == 0) {
        size = input.size() - index;
    }
    for (size_t i = 0; i < size; ++i) {
        if ((index + i) >= input.size()) {
            std::cerr << "Slice returned early" << std::endl;
            break;
        }
        output.push_back(input.at(index + i));
    }
    return output;
}

void PrintAscii(const std::vector<uint8_t>& data, size_t count) {
    if (count == 0) {
        count = data.size();
    }
    for (size_t i = 0; i < count; ++i) {
        std::cout << data[i] << " ";
    }
}

void Print(const std::vector<uint8_t>& data, size_t count) {
    if (count == 0) {
        count = data.size();
    }
    for (size_t i = 0; i < count; ++i) {
        std::cout << (int)data[i] << " ";
    }
}