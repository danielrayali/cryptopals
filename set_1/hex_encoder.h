#pragma once

#include <map>
#include <vector>

class HexEncoder {
public:
    HexEncoder() {
        for (char number = '0'; number <= '9'; ++number) {
            hex_table_.emplace(number, 0 + (number - '0'));
        }
        for (char letter = 'a'; letter <= 'f'; ++letter) {
            hex_table_.emplace(letter, 10 + (letter - 'a'));
        }
    }

    // input string:        "49276d"
    // ascii:                       49         27         6d
    // to bytes:            0b01001001 0b00100111 0b01101101
    // output vector index:          0          1          2
    std::vector<uint8_t> ToBytes(const std::string& hex_string) const {
        std::vector<uint8_t> bytes;
        for (size_t i = 0; i < hex_string.size(); i += 2) {
            bytes.emplace_back(this->HexToBinary(hex_string.at(i)) << 4 |
                               this->HexToBinary(hex_string.at(i + 1)));
        }
        return bytes;
    }

private:
    // TODO: Is there a better data structure, e.g. array with offsets?
    std::map<char, uint8_t> hex_table_;

    // HexToBinary('0') returns uint8_t(0)
    // HexToBinary('9') returns uint8_t(9)
    // HexToBinary('a') returns uint8_t(10)
    // HexToBinary('A') returns uint8_t(10)
    uint8_t HexToBinary(const char hex_letter) const {
        return hex_table_.at(hex_letter);
    }
};