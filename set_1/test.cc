#include <iostream>

#include "base64.h"
#include "bitset.h"
#include "aes.h"

int main(int, char*[]) {
    // Hamming distance test
    {
        std::string left("this is a test");
        std::string right("wokka wokka!!!");
        std::cout << "First string: " << left << std::endl;
        std::cout << "Second string: " << right << std::endl;
        std::cout << "Hamming distance: " << CalculateHammingDistance({left}, {right}) << std::endl;
    }

    // Base64 test
    Base64 base64;
    {
        std::vector<uint8_t> orig;
        for (size_t i = 0; i < 10000; ++i) {
            orig.push_back(rand());
        }
        std::vector<uint8_t> enc = base64.Encode(orig);
        std::vector<uint8_t> dec = base64.Decode(enc);
        std::vector<uint8_t> reenc = base64.Encode(dec);
        std::string enc_to_str = base64.ToString(enc);
        std::vector<uint8_t> enc_from_str = base64.FromString(enc_to_str);
        for (size_t i = 0; i < orig.size(); ++i) {
            if (enc[i] != reenc[i]) {
                std::cerr << "Error is Base64 string function at " << i << std::endl;
                return 1;
            }
            if (enc[i] != enc_from_str[i]) {
                std::cerr << "Error is Base64 string function at " << i << std::endl;
                return 1;
            }
            if (orig[i] != dec[i]) {
                std::cerr << "Error in Base64 at " << i << std::endl;
                return 1;
            }
        }
    }

    std::vector<uint8_t> key{ 0x54, 0x68, 0x61, 0x74, 0x73, 0x20, 0x6D, 0x79,
                              0x20, 0x4B, 0x75, 0x6E, 0x67, 0x20, 0x46, 0x75 };

    std::cout << "Square test:\n";
    std::vector<std::vector<uint8_t>> square_key = MakeSquareMatrix(key, 4);
    for (size_t i = 0; i < square_key.size(); i++) {
        PrintHex(square_key.at(i));
    }
    std::cout << std::endl;

    Aes aes;
    aes.SetKey(key);

    std::vector<uint8_t> plain_text{ 0x54, 0x77, 0x6F, 0x20, 0x4F, 0x6E, 0x65, 0x20,
                                     0x4E, 0x69, 0x6E, 0x65, 0x20, 0x54, 0x77, 0x6F };
    std::vector<uint8_t> cipher_text = aes.Encrypt(plain_text);

    std::vector<uint8_t> decrypted_text = aes.Decrypt(cipher_text);
    for (size_t i = 0; i < plain_text.size(); ++i) {
        if (plain_text[i] != decrypted_text[i]) {
            std::cerr << "Plain text/decrypted text mis-match, index " << i << std::endl;
            return 1;
        }
    }
    return 0;
}
