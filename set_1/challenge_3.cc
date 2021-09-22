#include <iostream>
#include <vector>
#include <cctype>

#include "hex_encoder.h"
#include "xor.h"

using namespace std;

int CountLetters(const std::vector<uint8_t>& input) {
    int count = 0;
    for (size_t i = 0; i < input.size(); ++i) {
        if (std::isalpha(input[i])) {
            count++;
        }
    }
    return count;
}

int main(int, char*[]) {
    std::vector<uint8_t> input = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!' };
    cout << "Hello, World! has " << CountLetters(input) << " letters" << endl;

    std::string input_str{"1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"};
    HexEncoder hex_encoder;
    input = hex_encoder.ToBytes(input_str);

    uint16_t key = 0;
    uint8_t max_key = 0;
    std::string max_output;
    std::vector<uint8_t> xord;
    int count = 0, max_count = -1;
    while (key < 256) {
        xord = XorSingle(input, key);
        count = CountLetters(xord);
        if (count > max_count) {
            max_count = count;
            max_key = key;
            max_output = std::string(xord.begin(), xord.end());
        }
        key++;
    }

    cout << "Max letter count was " << max_count << endl;
    cout << "Max letter key was " << max_key << endl;
    cout << "Max letter output was " << max_output << endl;

    return 0;
}
