#include <iostream>
#include <fstream>

#include "xor_key_finder.h"
#include "hex_encoder.h"

int main(int,char*[]) {
    HexEncoder encoder;
    std::ifstream input("4.txt");
    std::string line;
    XorKeyFinder finder;
    while (getline(input, line)) {
        std::vector<uint8_t> bytes = encoder.FromString(line);
        finder.Search(bytes);
    }
    finder.Print();
    return 0;
}
