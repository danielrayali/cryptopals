#include <iostream>
#include <string>
#include <fstream>
#include <limits>

#include "bitset.h"

int FindKeySize(std::ifstream& in) {
    float lowest_weight = std::numeric_limits<float>::max();
    int likely_keysize = 0;
    for (int i = 2; i < 40; ++i) {
        in.seekg(std::ios::beg);
        std::string first(i, 0), second(i, 0), third(i, 0), fourth(i, 0);
        in.read(first.data(), i);
        in.read(second.data(), i);
        in.read(third.data(), i);
        in.read(fourth.data(), i);
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

    std::ifstream in("6.txt");
    int key_size = FindKeySize(in);
    std::cout << "Key size: " << key_size << std::endl;
    return 0;
}