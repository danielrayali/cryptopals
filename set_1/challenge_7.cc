#include <iostream>
#include <fstream>

#include "aes_encoder.h"
#include "base64.h"
#include "file_reader.h"

int main(int, char*[]) {
    std::string input = FileReader::Read("7.txt");
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
