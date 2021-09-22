#include <iostream>
#include <vector>
#include <cctype>

#include "hex_encoder.h"
#include "xor_key_finder.h"

using namespace std;


int main(int, char*[]) {
    std::vector<uint8_t> input = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!' };
    cout << "Hello, World! has " << CountLetters(input) << " letters" << endl;

    std::string input_str{"1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"};
    HexEncoder hex_encoder;
    input = hex_encoder.ToBytes(input_str);

    XorKeyFinder finder;
    finder.Search(input);
    cout << "Max letter output was " << finder.GetMaxLetterString() << endl;

    return 0;
}
