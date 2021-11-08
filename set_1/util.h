#pragma once

#include <vector>
#include <cstdint>
#include <iostream>
#include <iomanip>

// Returns a slice of the input. If the requested end is beyond the size of the input, only the data that
// can be returned is.
// TODO: Remove this and use vector functions
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
        std::cout << data[i];
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

void PrintHex(const std::vector<uint8_t>& data) {
    for (size_t i = 0; i < data.size(); ++i) {
        std::cout << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(data[i]) << " " << std::dec;
    }
}

std::vector<std::vector<uint8_t>> MakeSquareMatrix(const std::vector<uint8_t>& data, const size_t size) {
    std::vector<std::vector<uint8_t>> matrix;
    for (size_t i = 0; i < size; ++i) {
        matrix.push_back({});
        for (size_t j = 0; j < size; ++j) {
            matrix.back().emplace_back(data.at(i * size + j));
        }
    }
    return matrix;
}

std::vector<uint8_t> Concat(const std::vector<std::vector<uint8_t>>& input) {
    std::vector<uint8_t> output;
    for (auto row : input) {
        for (auto item : row) {
            output.emplace_back(item);
        }
    }
    return output;
}

std::vector<std::vector<uint8_t>> Zeros(const size_t size) {
    std::vector<std::vector<uint8_t>> zeros(size);
    for (size_t i = 0; i < size; ++i) {
        zeros[i].resize(size, 0);
    }
    return zeros;
}