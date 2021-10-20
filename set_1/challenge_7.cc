#include <iostream>
#include <fstream>

#include "aes.h"
#include "base64.h"
#include "file_reader.h"
#include "hex_encoder.h"

int main(int, char*[]) {
    std::string base64_str = FileReader::Read("7.txt");
    Base64 base64;
    std::vector<uint8_t> base64_bytes = base64.FromString(base64_str);
    std::vector<uint8_t> encrypted = base64.Decode(base64_bytes);
    Aes aes;
    std::vector<uint8_t> decrypted = aes.Decrypt(encrypted);
    std::cout << "Decyrpted:\n" << (char*)decrypted.data() << std::endl;
    return 0;
}
