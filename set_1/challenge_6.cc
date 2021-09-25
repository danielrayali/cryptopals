#include <iostream>
#include <string>

#include "bitset.h"

int main(int, char*[]) {
    std::string left("this is a test");
    std::string right("wokka wokka!!!");
    std::cout << "First string: " << left << std::endl;
    std::cout << "Second string: " << right << std::endl;
    std::cout << "Hamming distance: " << CalculateHammingDistance({left}, {right}) << std::endl;
    return 0;
}