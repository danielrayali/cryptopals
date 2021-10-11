#pragma once

#include <array>
#include <vector>

class Base64 {
public:
    Base64() {
        for (char letter = 'A'; letter <= 'Z'; letter++) {
            bin_to_letter_[letter - 'A'] = letter;
            letter_to_bin_[letter] = (letter - 'A');
        }
        for (char letter = 'a'; letter <= 'z'; ++letter) {
            bin_to_letter_[26 + (letter - 'a')] = letter;
            letter_to_bin_[letter] = 26 + (letter - 'a');
        }
        for (char number = '0'; number <= '9'; ++number) {
            bin_to_letter_[52 + (number - '0')] = number;
            letter_to_bin_[number] = 52 + (number - '0');
        }
    }

    // Input bits/bytes:    AAAAAABB|BBBBCCCC|CCDDDDDD
    // Output bits/bytes:   XXAAAAAA|XXBBBBBB|XXCCCCCC|XXDDDDDD
    //                      X is don't care.
    std::vector<uint8_t> Encode(const std::vector<uint8_t>& bytes) const {
        int state = 0;
        std::vector<uint8_t> output;
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
        return output;
    }

    // Input bits/bytes:    XXAAAAAA|XXBBBBBB|XXCCCCCC|XXDDDDDD
    // Output bits/bytes:   AAAAAABB|BBBBCCCC|CCDDDDDD
    //                      X is don't care.
    std::vector<uint8_t> Decode(const std::vector<uint8_t>& bytes) const {
        std::vector<uint8_t> output;
        for (size_t i = 0; i < bytes.size(); i += 4) {
            output.emplace_back((bytes[i] & 0x3f) << 2);
            if ((i + 1) >= bytes.size()) {
                break;
            }
            output.back() |= ((bytes[i + 1] & 0x30) >> 4);
            output.emplace_back((bytes[i + 1] & 0x0f) << 4);
            if ((i + 2) >= bytes.size()) {
                break;
            }
            output.back() |= ((bytes[i + 2] & 0x3c) >> 2);
            output.emplace_back((bytes[i + 2] & 0x03) << 6);
            if ((i + 3) >= bytes.size()) {
                break;
            }
            output.back() |= (bytes[i + 3] & 0x3f);
        }
        return output;
    }

    std::string ToString(const std::vector<uint8_t>& encoded_bytes) const {
        std::string output;
        for (auto byte : encoded_bytes) {
            output.push_back(bin_to_letter_[byte]);
        }
        return output;
    }

    // Input would be "HUIfTQsPAh9PE048GmllH0kcDk4TAQsHThsBFkU2AB4BSWQgVB0dQzNTTmVS"
    // Output would be { }
    std::vector<uint8_t> FromString(const std::string& input) const {
        std::vector<uint8_t> output;
        for (auto letter : input) {
            output.push_back(letter_to_bin_[letter]);
        }
        return output;
    }

private:
    std::array<char, 64> bin_to_letter_;
    std::array<uint8_t, 64> letter_to_bin_;
};
