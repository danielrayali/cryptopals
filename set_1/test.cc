#include <iostream>

#include "base64.h"
#include "bitset.h"

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

    return 0;
}
