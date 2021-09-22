#include <iostream>

#include "xor.h"
#include "hex_encoder.h"

int main(int,char*[]) {
    std::string input1_str("Burning 'em, if you ain't quick and nimble");
    std::string input2_str("I go crazy when I hear a cymbal");
    std::string key_str("ICE");

    std::vector<uint8_t> input1(input1_str.begin(), input1_str.end());
    std::vector<uint8_t> input2(input2_str.begin(), input2_str.end());
    std::vector<uint8_t> key(key_str.begin(), key_str.end());

    HexEncoder hex_encoder;
    std::cout << "First line: " << hex_encoder.ToString(XorRepeat(input1, key)) << std::endl;
    std::cout << "Expected:   0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272" << std::endl;
    std::cout << "Second line: " << hex_encoder.ToString(XorRepeat(input2, key)) << std::endl;
    std::cout << "Expected:    a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f" << std::endl;
    return 0;
}
