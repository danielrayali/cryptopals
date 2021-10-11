#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <sstream>

#include "bitset.h"
#include "base64.h"
#include "xor_key_finder.h"
#include "util.h"

int FindKeySize(const std::vector<uint8_t>& in) {
    float lowest_weight = std::numeric_limits<float>::max();
    int likely_keysize = 0;
    for (int i = 2; i < 40; ++i) {
        std::vector<uint8_t> first  = Slice(in,     0, i);
        std::vector<uint8_t> second = Slice(in,     i, i);
        std::vector<uint8_t> third  = Slice(in, i * 2, i);
        std::vector<uint8_t> fourth = Slice(in, i * 3, i);
        float distance[6] = {
            static_cast<float>(CalculateHammingDistance(first, second)),
            static_cast<float>(CalculateHammingDistance(first, third)),
            static_cast<float>(CalculateHammingDistance(first, fourth)),
            static_cast<float>(CalculateHammingDistance(second, third)),
            static_cast<float>(CalculateHammingDistance(second, fourth)),
            static_cast<float>(CalculateHammingDistance(third, fourth))
        };
        float weight = distance[0] + distance[1] + distance[2] + distance[3] + distance[4] + distance[5];
        weight /= 6.0f;
        weight /= static_cast<float>(i);
        if (weight < lowest_weight) {
            lowest_weight = weight;
            likely_keysize = i;
        }
    }
    return likely_keysize;
}

int main(int, char*[]) {
    std::string left("this is a test");
    std::string right("wokka wokka!!!");
    std::cout << "First string: " << left << std::endl;
    std::cout << "Second string: " << right << std::endl;
    std::cout << "Hamming distance: " << CalculateHammingDistance({left}, {right}) << std::endl;

    Base64 base64;
    std::vector<uint8_t> orig{ 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF };
    std::vector<uint8_t> enc = base64.Encode(orig);
    std::vector<uint8_t> dec = base64.Decode(enc);
    for (size_t i = 0; i < orig.size(); ++i) {
        if (orig[i] != dec[i]) {
            std::cerr << "Error in Base64 at " << i << std::endl;
            return 1;
        }
    }

    std::ifstream input_file("6.txt");
    std::stringstream input_stream;
    while (!input_file.eof()) {
        std::string line;
        std::getline(input_file, line);
        input_stream << line;
    }
    std::string input = input_stream.str();

    std::vector<uint8_t> base64_bytes = base64.FromString(input);
    std::vector<uint8_t> encrypted = base64.Decode(base64_bytes);
    size_t key_size = FindKeySize(encrypted);
    std::cout << "Key size: " << key_size << std::endl;

    // Break input into blocks
    std::vector<std::vector<uint8_t>> blocks;
    for (size_t i = 0; i < base64_bytes.size();) {
        blocks.emplace_back();
        for (size_t j = 0; (j < key_size) && (i < base64_bytes.size()); ++j) {
            blocks.back().emplace_back(base64_bytes.at(i++));
        }
    }

    for (int i = 0; i < 10; ++i) {
        for (size_t j = 0; j < blocks[i].size(); ++j) {
            std::cout << (int)blocks[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Transpose blocks
    std::vector<std::vector<uint8_t>> transposed;
    for (size_t i = 0; i < blocks.size(); ++i) {
        for (size_t j = 0; j < blocks.at(i).size(); ++j) {
            if (transposed.size() <= (j% key_size)) {
                transposed.push_back({});
            }
            transposed[j % key_size].push_back(blocks.at(i).at(j));
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 10; ++j) {
            std::cout << (int)transposed[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::vector<uint8_t> keys;
    for (size_t i = 0; i < transposed.size(); ++i) {
        XorKeyFinder finder;
        finder.Search(transposed.at(i));
        keys.push_back(finder.GetMaxLetterKey());
    }

    std::cout << "Key found: ";
    for (auto key : keys) {
        std::cout << key << " ";
    }
    std::cout << std::endl;

/*
    XorRepeatEncoder encoder;
    encoder.SetKey(keys);
    std::vector<uint8_t> output = encoder.Encode(encrypted);
    std::string output_str(output.begin(), output.end());
    std::cout << "Output: " << output_str << std::endl;
    */
    return 0;
}