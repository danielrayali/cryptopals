#pragma once

#include <array>
#include <vector>

typedef std::vector<uint8_t> Base64Bytes;

class Base64Encoder {
public:
    Base64Encoder() {
        for (char letter = 'A'; letter <= 'Z'; letter++) {
            base64_table_[letter - 'A'] = letter;
        }
        for (char letter = 'a'; letter <= 'z'; ++letter) {
            base64_table_[26 + (letter - 'a')] = letter;
        }
        for (char number = '0'; number <= '9'; ++number) {
            base64_table_[52 + (number - '0')] = number;
        }
    }

    // Input bits/bytes:    AAAAAABB|BBBBCCCC|CCDDDDDD
    // Output bits/bytes:   XXAAAAAA|XXBBBBBB|XXCCCCCC|XXDDDDDD
    //                      X is don't care.
    static Base64Bytes Encode(const std::vector<uint8_t>& bytes) {
        int state = 0;
        Base64Bytes output;
        for (size_t i = 0; i < bytes.size(); ++i) {
            if (state == 0) {
                output.emplace_back((bytes[i] & 0xfc) >> 2);
                output.emplace_back((bytes[i] & 0x03) << 4);
                state++;
            } else if (state == 1) {
                output.back() |= ((bytes[i] & 0xf0) >> 4);
                output.emplace_back((bytes[i] & 0x0f) << 2);
                state++;
            } else if (state == 2) {
                output.back() |= ((bytes[i] & 0xc0) >> 6);
                output.emplace_back(bytes[i] & 0x3f);
                state = 0;
            }
        }
        // TODO check padding on inputs that do not divide evenly by three
        return output;
    }

    std::string ToString(const Base64Bytes& encoded_bytes) const {
        std::string output;
        for (auto byte : encoded_bytes) {
            output.push_back(this->BinaryToBase64Letter(byte));
        }
        return output;
    }

private:
    std::array<char, 64> base64_table_;

    char BinaryToBase64Letter(const uint8_t value) const {
        return base64_table_[value];
    }
};
