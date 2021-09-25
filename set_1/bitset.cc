#include "bitset.h"

#include <iostream>

int CalculateHammingDistance(const Bitset& left, const Bitset& right) {
    if (left.bitset_.size() != right.bitset_.size()) {
        std::cerr << "Calculating Hamming distance with unequal sizes not implemented" << std::endl;
        return -1;
    }

    int count = 0;
    for (size_t i = 0; i < left.bitset_.size(); ++i) {
        if (left.bitset_[i] != right.bitset_[i]) {
            count++;
        }
    }
    return count;
}
