#include <iostream>

#include "hex_encoder.h"
#include "base64.h"

int main(int, char*[]) {
    // Challenge 1: Convert hex nibble string to base64 string values
    //
    // decimal: 4      9      2      7      6      d
    // binary:  0b0100 0b1001 0b0010 0b0111 0b0110 0b1101
    //
    // base64:  0b010010 0b010010 0b011101 0b101101
    // base64:  S        S        d        t

    std::string input("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d");
    std::string expected("SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t");

    HexEncoder hex_encoder;
    std::vector<uint8_t> bytes = hex_encoder.FromString(input);

    Base64 base64;
    std::vector<uint8_t> base64_bytes = base64.Encode(bytes);
    std::string output = base64.ToString(base64_bytes);
    std::cout << "input:    " << input << std::endl;
    std::cout << "expected: " << expected << std::endl;
    std::cout << "output:   " << output << std::endl;
    if (output != expected) {
        std::cerr << "ERROR" << std::endl;
        return 1;
    }
    return 0;
}
