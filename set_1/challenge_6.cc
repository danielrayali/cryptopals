#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <sstream>

#include "bitset.h"
#include "base64.h"
#include "xor_key_finder.h"
#include "util.h"

int FindKeySize(const std::vector<uint8_t>& input) {
    float lowest_distance = std::numeric_limits<float>::max();
    size_t key_size = 0;
    for (size_t i = 2; i < 40; ++i) {
        float distance = CalculateHammingDistance(Slice(input, 0, i), Slice(input, i, i));
        distance /= static_cast<float>(i);
        if (distance < lowest_distance) {
            lowest_distance = distance;
            key_size = i;
        }
    }
    return key_size;
}

int main(int, char* argv[]) {
    // Hamming distance test
    std::string left("this is a test");
    std::string right("wokka wokka!!!");
    std::cout << "First string: " << left << std::endl;
    std::cout << "Second string: " << right << std::endl;
    std::cout << "Hamming distance: " << CalculateHammingDistance({left}, {right}) << std::endl;

    // Base64 test
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

    // Read the initial input file
    std::ifstream input_file("6.txt");
    std::stringstream input_stream;
    while (!input_file.eof()) {
        std::string line;
        std::getline(input_file, line);
        input_stream << line;
    }
    std::string input = input_stream.str();

    // Decode base64
    std::vector<uint8_t> base64_bytes = base64.FromString(input);
    std::vector<uint8_t> encrypted = base64.Decode(base64_bytes);

    // Find the key size
    size_t key_size = atoi(argv[1]);
    // size_t key_size = FindKeySize(encrypted);
    std::cout << "Key size: " << key_size << std::endl;

    // Break input into blocks
    std::vector<std::vector<uint8_t>> blocks;
    for (size_t i = 0; i < base64_bytes.size();) {
        blocks.emplace_back();
        for (size_t j = 0; (j < key_size) && (i < base64_bytes.size()); ++j) {
            blocks.back().emplace_back(base64_bytes.at(i++));
        }
    }

    // std::cout << "Blocks:\n";
    // for (int i = 0; i < 10; ++i) {
    //     for (size_t j = 0; j < key_size; ++j) {
    //         std::cout << (int)blocks[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

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

    // std::cout << "Transposed: " << std::endl;
    // for (size_t i = 0; i < key_size; ++i) {
    //     for (size_t j = 0; j < 10; ++j) {
    //         std::cout << (int)transposed[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // Search for the key based on the transposed size
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

    // Decode the encrypted string
    XorRepeatEncoder encoder;
    encoder.SetKey(keys);
    std::vector<uint8_t> output = encoder.Encode(encrypted);
    std::string output_str(output.begin(), output.end());
    std::cout << "Output: " << output_str.substr(0, 20) << std::endl;

    return 0;
}