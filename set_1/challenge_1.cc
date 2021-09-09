#include <iostream>
#include <fmt/format.h>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <array>

using namespace std;

class Converter {
public:
    Converter() {
        for (char number = '0'; number <= '9'; ++number) {
            hex_table_.emplace(number, 0 + (number - '0'));
            base64_table_[52 + (number - '0')] = number;
        }
        for (char letter = 'a'; letter <= 'f'; ++letter) {
            hex_table_.emplace(letter, 10 + (letter - 'a'));
            base64_table_[26 + (letter - 'a')] = letter;
        }
        for (char letter = 'g'; letter <= 'z'; letter++) {
            base64_table_[32 + (letter - 'g')] = letter;
        }
        for (char letter = 'A'; letter <= 'Z'; letter++) {
            base64_table_[letter - 'A'] = letter;
        }
    }

    // HexToBinary('0') returns uint8_t(0)
    // HexToBinary('9') returns uint8_t(9)
    // HexToBinary('a') returns uint8_t(10)
    // HexToBinary('A') returns uint8_t(10)
    uint8_t HexToBinary(const char hex_letter) {
        return hex_table_.at(hex_letter);
    }

    //
    char BinaryToBase64Letter(const uint8_t value) {
        return base64_table_[value];
    }

private:
    // TODO: Is there a better data structure, e.g. array with offsets?
    std::map<char, uint8_t> hex_table_;
    std::array<char, 64> base64_table_;
};

static Converter gConverter;

// input string: "49276d"
// ascii:                       49         27         6d
// to bytes:            0b01001001 0b00100111 0b01101101
// output vector index:          0          1          2
std::vector<uint8_t> HexStringToBytes(const std::string& hex_string) {
    std::vector<uint8_t> bytes;
    for (size_t i = 0; i < hex_string.size(); i += 2) {
        bytes.emplace_back(gConverter.HexToBinary(hex_string.at(i)) << 4 |
                           gConverter.HexToBinary(hex_string.at(i + 1)));
    }
    return bytes;
}

// Input bits/bytes:    AAAAAABB|BBBBCCCC|CCDDDDDD
// Output bits/bytes:   XXAAAAAA|XXBBBBBB|XXCCCCCC|XXDDDDDD
//                      X is don't care.
std::vector<uint8_t> BytesToBase64Binary(const std::vector<uint8_t>& bytes) {
    int state = 0;
    size_t output_idx = 0;
    std::vector<uint8_t> output;
    output.resize(bytes.size()*2);
    for (size_t i = 0; i < bytes.size(); ++i) {
        if (state == 0) {
            output[output_idx] = (bytes[i] & 0xfc) >> 2;
            output_idx++;
            output[output_idx] = (bytes[i] & 0x03) << 4;
            state++;
        } else if (state == 1) {
            output[output_idx] |= (bytes[i] & 0xf0) >> 4;
            output_idx++;
            output[output_idx] = (bytes[i] & 0x0f) << 2;
            state++;
        } else if (state == 2) {
            output[output_idx] |= (bytes[i] & 0xc0) >> 6;
            output_idx++;
            output[output_idx] = (bytes[i] & 0x3f);
            output_idx++;
            state = 0;
        }
    }
    // TODO check padding on inputs that do not divide evenly by three
    output.resize(output_idx);
    return output;
}

std::string Base64BinaryToString(const std::vector<uint8_t>& base64_binary) {
    static Converter converter;
    std::stringstream output;
    for (auto value : base64_binary) {
        output << converter.BinaryToBase64Letter(value);
    }
    return output.str();
}

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
    std::vector<uint8_t> bytes = HexStringToBytes(input);
    std::vector<uint8_t> base64_binary = BytesToBase64Binary(bytes);
    std::string output = Base64BinaryToString(base64_binary);
    std::cout << "input:    " << input << std::endl;
    std::cout << "expected: " << expected << std::endl;
    std::cout << "output:   " << output << std::endl;
    if (output != expected) {
        std::cout << "ERROR" << std::endl;
    }
    return 0;
}
