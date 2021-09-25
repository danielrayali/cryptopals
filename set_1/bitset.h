#pragma once

#include <string>
#include <vector>

class Bitset {
public:
    Bitset(const std::string& data) {
        for (auto datum : data) {
            for (int mask = 0x1; mask < 0x100; mask <<= 1) {
                bitset_.push_back(datum & mask);
            }
        }
    }

    friend int CalculateHammingDistance(const Bitset& left, const Bitset& right);

private:
    std::vector<bool> bitset_;
};

int CalculateHammingDistance(const Bitset& left, const Bitset& right);
