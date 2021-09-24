#include <iostream>
#include <vector>
#include <fstream>

#include "xor.h"
#include "hex_encoder.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Reapting key XOR program\n\n";
        std::cout << "Usage: " << argv[0] << " <KEY> <IN FILE> <OUT FILE>\n" << std::endl;
        return 1;
    }

    std::ifstream in_stream(argv[2], std::ios::binary);
    std::ofstream out_stream(argv[3], std::ios::binary);

    XorRepeatEncoder xor_encoder;
    std::string key_str(argv[1]);
    xor_encoder.SetKey({key_str.begin(), key_str.end()});

    HexEncoder hex_encoder;
    uint8_t input = 0, output = 0;
    in_stream.read(reinterpret_cast<char*>(&input), 1);
    while (!in_stream.eof()) {
        output = xor_encoder.Encode(input);
        out_stream.write(reinterpret_cast<char*>(&output), 1);
        in_stream.read(reinterpret_cast<char*>(&input), 1);
    }
    return 0;
}
