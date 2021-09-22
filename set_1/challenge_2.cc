#include <iostream>
#include <string>

#include "xor.h"
#include "hex_encoder.h"

int main(int, char*[]) {
    std::string left("1c0111001f010100061a024b53535009181c");
    std::string right("686974207468652062756c6c277320657965");
    std::string expected("746865206b696420646f6e277420706c6179");

    HexEncoder hex_encoder;
    std::vector<uint8_t> left_bytes = hex_encoder.ToBytes(left);
    std::vector<uint8_t> right_bytes = hex_encoder.ToBytes(right);
    std::vector<uint8_t> xored_bytes = XorEqual(left_bytes, right_bytes);

    std::string xored = hex_encoder.ToString(xored_bytes);
    std::cout << "left:     " << left << std::endl;
    std::cout << "right:    " << right << std::endl;
    std::cout << "expected: " << expected << std::endl;
    std::cout << "result:   " << xored << std::endl;

    if (expected != xored) {
        std::cerr << "ERROR" << std::endl;
        return 1;
    }

    return 0;
}
