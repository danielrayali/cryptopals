#pragma once

#include <cstdint>
#include <vector>
#include <cmath>
#include <utility>

#include "xor.h"
#include "util.h"

class Aes {
public:
    Aes() = default;

    ~Aes() = default;

    void SetKey(const std::vector<uint8_t>& key) {
        this->GenerateRoundKeys(key);
    }

    std::vector<uint8_t> Encrypt(const std::vector<uint8_t>& plain_text) {
        std::vector<uint8_t> cipher_text = XorEqual(plain_text, round_keys_[0]);
        std::cout << "After round 0 add roundkey: ";
        PrintHex(cipher_text);
        std::cout << std::endl;

        for (size_t i = 0; i < cipher_text.size(); ++i) {
            cipher_text[i] = this->SBox(cipher_text[i]);
        }
        std::cout << "After round 1 substitutes: ";
        PrintHex(cipher_text);
        std::cout << std::endl;

        this->ShiftRow(cipher_text);
        std::cout << "After round 1 row shifts: ";
        PrintHex(cipher_text);
        std::cout << std::endl;

        this->MixColumn(cipher_text);
        std::cout << "After round 1 mix column: ";
        PrintHex(cipher_text);
        std::cout << std::endl;

        std::cout << "After round 1 key add: ";
        PrintHex(XorEqual(cipher_text, round_keys_[1]));
        std::cout << std::endl;

        return cipher_text;
    }

    std::vector<uint8_t> Decrypt(const std::vector<uint8_t>& cipher_text) {

        return cipher_text;
    }

private:
    std::vector<uint8_t> key_;

    std::vector<std::vector<uint8_t>> round_keys_;

    std::vector<std::vector<uint8_t>> round_constants_ = {
        { 0x01, 0x00, 0x00, 0x00 },
        { 0x02, 0x00, 0x00, 0x00 },
        { 0x04, 0x00, 0x00, 0x00 },
        { 0x08, 0x00, 0x00, 0x00 },
        { 0x10, 0x00, 0x00, 0x00 },
        { 0x20, 0x00, 0x00, 0x00 },
        { 0x40, 0x00, 0x00, 0x00 },
        { 0x80, 0x00, 0x00, 0x00 },
        { 0x1B, 0x00, 0x00, 0x00 },
        { 0x36, 0x00, 0x00, 0x00 }
    };

    const uint8_t s_box_[256] = {
        0x63 ,0x7c ,0x77 ,0x7b ,0xf2 ,0x6b ,0x6f ,0xc5 ,0x30 ,0x01 ,0x67 ,0x2b ,0xfe ,0xd7 ,0xab ,0x76,
        0xca ,0x82 ,0xc9 ,0x7d ,0xfa ,0x59 ,0x47 ,0xf0 ,0xad ,0xd4 ,0xa2 ,0xaf ,0x9c ,0xa4 ,0x72 ,0xc0,
        0xb7 ,0xfd ,0x93 ,0x26 ,0x36 ,0x3f ,0xf7 ,0xcc ,0x34 ,0xa5 ,0xe5 ,0xf1 ,0x71 ,0xd8 ,0x31 ,0x15,
        0x04 ,0xc7 ,0x23 ,0xc3 ,0x18 ,0x96 ,0x05 ,0x9a ,0x07 ,0x12 ,0x80 ,0xe2 ,0xeb ,0x27 ,0xb2 ,0x75,
        0x09 ,0x83 ,0x2c ,0x1a ,0x1b ,0x6e ,0x5a ,0xa0 ,0x52 ,0x3b ,0xd6 ,0xb3 ,0x29 ,0xe3 ,0x2f ,0x84,
        0x53 ,0xd1 ,0x00 ,0xed ,0x20 ,0xfc ,0xb1 ,0x5b ,0x6a ,0xcb ,0xbe ,0x39 ,0x4a ,0x4c ,0x58 ,0xcf,
        0xd0 ,0xef ,0xaa ,0xfb ,0x43 ,0x4d ,0x33 ,0x85 ,0x45 ,0xf9 ,0x02 ,0x7f ,0x50 ,0x3c ,0x9f ,0xa8,
        0x51 ,0xa3 ,0x40 ,0x8f ,0x92 ,0x9d ,0x38 ,0xf5 ,0xbc ,0xb6 ,0xda ,0x21 ,0x10 ,0xff ,0xf3 ,0xd2,
        0xcd ,0x0c ,0x13 ,0xec ,0x5f ,0x97 ,0x44 ,0x17 ,0xc4 ,0xa7 ,0x7e ,0x3d ,0x64 ,0x5d ,0x19 ,0x73,
        0x60 ,0x81 ,0x4f ,0xdc ,0x22 ,0x2a ,0x90 ,0x88 ,0x46 ,0xee ,0xb8 ,0x14 ,0xde ,0x5e ,0x0b ,0xdb,
        0xe0 ,0x32 ,0x3a ,0x0a ,0x49 ,0x06 ,0x24 ,0x5c ,0xc2 ,0xd3 ,0xac ,0x62 ,0x91 ,0x95 ,0xe4 ,0x79,
        0xe7 ,0xc8 ,0x37 ,0x6d ,0x8d ,0xd5 ,0x4e ,0xa9 ,0x6c ,0x56 ,0xf4 ,0xea ,0x65 ,0x7a ,0xae ,0x08,
        0xba ,0x78 ,0x25 ,0x2e ,0x1c ,0xa6 ,0xb4 ,0xc6 ,0xe8 ,0xdd ,0x74 ,0x1f ,0x4b ,0xbd ,0x8b ,0x8a,
        0x70 ,0x3e ,0xb5 ,0x66 ,0x48 ,0x03 ,0xf6 ,0x0e ,0x61 ,0x35 ,0x57 ,0xb9 ,0x86 ,0xc1 ,0x1d ,0x9e,
        0xe1 ,0xf8 ,0x98 ,0x11 ,0x69 ,0xd9 ,0x8e ,0x94 ,0x9b ,0x1e ,0x87 ,0xe9 ,0xce ,0x55 ,0x28 ,0xdf,
        0x8c ,0xa1 ,0x89 ,0x0d ,0xbf ,0xe6 ,0x42 ,0x68 ,0x41 ,0x99 ,0x2d ,0x0f ,0xb0 ,0x54 ,0xbb ,0x16 };

    inline uint8_t MixColumnMultiply(uint8_t times, uint8_t data) {
        if (times == 3) {
            return (((data * 2) ^ (data & 0x80 ? 0x1B : 0)) ^ data);
        } else if (times == 2) {
            return ((data * 2) ^ (data & 0x80 ? 0x1B : 0));
        } else {
            return data;
        }
    }

    void MixColumn(std::vector<uint8_t>& data) {
        size_t size = sqrt(data.size());
        std::vector<std::vector<uint8_t>> square = MakeSquareMatrix(data, size);
        static std::vector<std::vector<uint8_t>> fixed = {
            { 0x02, 0x01, 0x01, 0x03 },
            { 0x03, 0x02, 0x01, 0x01 },
            { 0x01, 0x03, 0x02, 0x01 },
            { 0x01, 0x01, 0x03, 0x02 }
        };

        // Destination loop
        std::vector<std::vector<uint8_t>> output = Zeros(size);
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                std::cout << "For [" << i << "][" << j << "] = \n";
                output[i][j] = 0;
                for (size_t k = 0; k < size; ++k) {
                    std::cout << k << ' ' << j << " * " << i << ' ' << k << std::endl;
                    std::cout << std::hex << (int)fixed[k][j] << " " << (int)square[i][k];
                    output[i][j] ^= MixColumnMultiply(fixed[k][j], square[i][k]);
                    std::cout << " = " << std::hex << (int)(MixColumnMultiply(fixed[k][j], square[i][k])) << std::endl;
                }
                std::cout << "output: " << std::hex << (int)output[i][j] << std::endl;
            }
        }

        data = Concat(output);
    }

    void ShiftRow(std::vector<uint8_t>& data) {
        std::vector<uint8_t> source(data);
        size_t square_size = sqrt(data.size());
        for (size_t i = 0; i < square_size; ++i) {
            for (size_t j = 1; j < square_size; ++j) {
                data[i * square_size + j] = source[(((i + j) % square_size) * square_size) + j];
            }
        }
    }

    void GenerateRoundKeys(const std::vector<uint8_t>& key) {
        round_keys_ = std::vector<std::vector<uint8_t>>{ 1, key };
        std::cout << "Round key[0]: ";
        PrintHex(round_keys_[0]);
        std::cout << std::endl;

        for (size_t i = 0; i < 10; ++i) {
            round_keys_.emplace_back(this->GetRoundKey(round_keys_[i], i));
            std::cout << "Round key[" << i+1 << "]: ";
            PrintHex(round_keys_.back());
            std::cout << std::endl;
        }
    }

    inline uint8_t SBox(const uint8_t value) {
        return s_box_[value];
    }

    std::vector<uint8_t> GetRoundKey(const std::vector<uint8_t>& prev_key, const int round) {
        std::vector<std::vector<uint8_t>> w;
        for (size_t i = 0 ; i < 4; ++i) {
            w.push_back({});
            std::cout << "w[" << i << "]: ";
            for (size_t j = 0; j < 4; ++j) {
                w.back().push_back(prev_key[(i * 4) + j]);
                std::cout << std::hex << (int)w.back().back() << " ";
            }
            std::cout << std::endl;
        }

        w.emplace_back(XorEqual(w[0], g_func(w[3], round_constants_[round])));
        std::cout << "w[" << 4 << "]: ";
        PrintHex(w.back());
        std::cout << std::endl;

        for (size_t i = 1; i < 4; ++i) {
            std::cout << "w[" << i+4 << "]: ";
            w.emplace_back(XorEqual(w[i], w[i+3]));
            PrintHex(w.back());
            std::cout << std::endl;
        }

        return Concat( { w.begin() + 4, w.end() } );
    }

    std::vector<uint8_t> g_func(const std::vector<uint8_t>& input, const std::vector<uint8_t>& round_constant) {
        if (input.size() != 4) {
            throw std::runtime_error("Erroneous size passed to g()");
        }

        // Circular byte shift left
        std::vector<uint8_t> output{input};
        output.push_back(output[0]);
        output.erase(output.begin());

        std::cout << "Shifted:              ";
        PrintHex(output);
        std::cout << std::endl;

        // Byte substitution (S-Box)
        for (size_t i = 0; i < output.size(); ++i) {
            output[i] = this->SBox(output[i]);
        }

        std::cout << "S-Boxed:              ";
        PrintHex(output);
        std::cout << std::endl;

        std::cout << "Round constant:       ";
        PrintHex(round_constant);
        std::cout << std::endl;

        // Add round constant
        output = XorEqual(output, round_constant);

        std::cout << "After round constant: ";
        PrintHex(output);
        std::cout << std::endl;

        return output;
    }
};
