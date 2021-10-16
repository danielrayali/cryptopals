#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <sstream>

#include "bitset.h"
#include "base64.h"
#include "xor_key_finder.h"
#include "util.h"
#include "file_reader.h"

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

// int main(int argc, char* argv[]) {
int main(int , char* []) {
    // Hamming distance test
    {
        std::string left("this is a test");
        std::string right("wokka wokka!!!");
        std::cout << "First string: " << left << std::endl;
        std::cout << "Second string: " << right << std::endl;
        std::cout << "Hamming distance: " << CalculateHammingDistance({left}, {right}) << std::endl;
    }

    // Base64 test
    Base64 base64;
    {
        std::vector<uint8_t> orig;
        for (size_t i = 0; i < 10000; ++i) {
            orig.push_back(rand());
        }
        std::vector<uint8_t> enc = base64.Encode(orig);
        std::vector<uint8_t> dec = base64.Decode(enc);
        std::vector<uint8_t> reenc = base64.Encode(dec);
        std::string enc_to_str = base64.ToString(enc);
        std::vector<uint8_t> enc_from_str = base64.FromString(enc_to_str);
        for (size_t i = 0; i < orig.size(); ++i) {
            if (enc[i] != reenc[i]) {
                std::cerr << "Error is Base64 string function at " << i << std::endl;
                return 1;
            }
            if (enc[i] != enc_from_str[i]) {
                std::cerr << "Error is Base64 string function at " << i << std::endl;
                return 1;
            }
            if (orig[i] != dec[i]) {
                std::cerr << "Error in Base64 at " << i << std::endl;
                return 1;
            }
        }
    }

    // Read the initial input file
    std::string input = FileReader::Read("6.txt");

    // Decode base64
    std::cout << input.substr(3780) << std::endl;
    std::vector<uint8_t> base64_bytes = base64.FromString(input);
    std::vector<uint8_t> encrypted = base64.Decode(base64_bytes);

    // Find the key size
    size_t key_size = FindKeySize(encrypted);

    // Break input into blocks
    std::vector<std::vector<uint8_t>> blocks;
    size_t num_blocks = encrypted.size() / key_size + 1;
    size_t last_block = encrypted.size() % key_size;
    std::cout << "Input size: " << encrypted.size() << std::endl;
    std::cout << "Key size: " << key_size << std::endl;
    std::cout << "Num blocks: " << num_blocks << std::endl;
    std::cout << "Last block: " << last_block << std::endl;
    for (size_t i = 0; i < num_blocks - 1; ++i) {
        blocks.emplace_back();
        for (size_t j = 0; j < key_size; ++j) {
            blocks.back().emplace_back(encrypted.at(i*key_size + j));
        }
    }

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
    std::cout << "Output: " << output_str << std::endl;

    return 0;
}