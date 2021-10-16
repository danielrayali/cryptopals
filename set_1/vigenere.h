#pragma once

#include <vector>
#include <iostream>

#include "xor_key_finder.h"
#include "xor.h"

class Vigenere {
public:
    Vigenere() = default;

    ~Vigenere() = default;

    std::vector<uint8_t> AttemptDecode(const std::vector<uint8_t>& encrypted) {
        // Find the key size
        size_t key_size = this->FindKeySize(encrypted);

        // Break input into blocks
        std::vector<std::vector<uint8_t>> blocks;
        size_t num_blocks = encrypted.size() / key_size + 1;
        size_t last_block = encrypted.size() % key_size;
        for (size_t i = 0; i < num_blocks - 1; ++i) {
            blocks.emplace_back();
            for (size_t j = 0; j < key_size; ++j) {
                blocks.back().emplace_back(encrypted.at(i*key_size + j));
            }
        }

        // Account for last block that may not fit into the key size
        if (last_block > 0) {
            blocks.emplace_back();
            for (size_t i = 0; i < last_block; ++i) {
                blocks.back().push_back(encrypted.at((num_blocks-1) * key_size + i));
            }
        }

        // Transpose blocks
        std::vector<std::vector<uint8_t>> transposed(key_size, std::vector<uint8_t>({}));
        for (size_t i = 0; i < key_size; ++i) {
            for (size_t j = 0; j < blocks.size(); ++j) {
                if (blocks.at(j).size() > i) {
                    transposed.at(i).push_back(blocks.at(j).at(i));
                }
            }
        }

        // Search for the key based on the transposed size
        std::vector<uint8_t> keys;
        for (size_t i = 0; i < transposed.size(); ++i) {
            XorKeyFinder finder;
            finder.Search(transposed.at(i));
            keys.push_back(finder.GetMaxLetterKey());
        }

        // Decode the encrypted string
        XorRepeatEncoder encoder;
        encoder.SetKey(keys);
        return encoder.Encode(encrypted);
    }

private:
    int FindKeySize(const std::vector<uint8_t>& input) {
        float lowest_distance = std::numeric_limits<float>::max();
        size_t key_size = 0;
        for (size_t i = 2; i < 40; ++i) {
            float distance = CalculateHammingDistance(Slice(input, 0, i), Slice(input, i, i)) / (float(i));
            distance += CalculateHammingDistance(Slice(input, 0, i), Slice(input, i * 2, i)) / (float(i));
            distance += CalculateHammingDistance(Slice(input, 0, i), Slice(input, i * 3, i)) / (float(i));
            distance += CalculateHammingDistance(Slice(input, i, i), Slice(input, i * 2, i)) / (float(i));
            distance += CalculateHammingDistance(Slice(input, i, i), Slice(input, i * 3, i)) / (float(i));
            distance += CalculateHammingDistance(Slice(input, i * 2, i), Slice(input, i * 3, i)) / (float(i));
            distance /= static_cast<float>(6);
            if (distance < lowest_distance) {
                lowest_distance = distance;
                key_size = i;
            }
        }
        return key_size;
    }
};
