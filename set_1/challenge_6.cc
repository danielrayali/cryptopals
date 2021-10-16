#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <sstream>

#include "bitset.h"
#include "base64.h"
#include "xor_key_finder.h"
#include "util.h"
#include "file_reader.h"
#include "vigenere.h"

// int main(int argc, char* argv[]) {
int main(int , char* []) {
    // Read the initial input file
    std::string input = FileReader::Read("6.txt");

    // Decode base64
    std::cout << input.substr(3780) << std::endl;
    Base64 base64;
    std::vector<uint8_t> base64_bytes = base64.FromString(input);
    std::vector<uint8_t> encrypted = base64.Decode(base64_bytes);

    // Attempt decode and display results
    Vigenere vigenere;
    std::vector<uint8_t> decrypted = vigenere.AttemptDecode(encrypted);
    std::string decrypted_str(decrypted.begin(), decrypted.end());
    std::cout << "Decrypted:\n" << decrypted_str << std::endl;

    return 0;
}