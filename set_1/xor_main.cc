#include <iostream>
#include <vector>

#include "xor.h"
#include "hex_encoder.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " --key <KEY>" << std::endl;
        return 1;
    }
    std::string key_str(argv[2]);
    HexEncoder hex_encoder;
    std::vector<uint8_t> key{key_str.begin(), key_str.end()};
    std::vector<uint8_t> buffer;
    int8_t in = 12;
    while (!std::cin.eof()) {
        buffer.clear();
        std::cin.read(reinterpret_cast<char*>(&in), 1);
        while ((buffer.size() < 4096) && !std::cin.eof()) {
            buffer.push_back(in);
            std::cin.read(reinterpret_cast<char*>(&in), 1);
        }
        std::vector<uint8_t> xor_out = XorRepeat(buffer, key);
        std::string output = hex_encoder.ToString(XorRepeat(buffer, key));
        std::cout << hex_encoder.ToString(XorRepeat(buffer, key)) << std::endl;
    }
    return 0;
}
