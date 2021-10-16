#pragma once

#include <fstream>
#include <string>
#include <sstream>

class FileReader {
public:
    static std::string Read(const std::string& path) {
        std::ifstream input_file(path);
        std::stringstream input_stream;
        while (!input_file.eof()) {
            std::string line;
            std::getline(input_file, line);
            input_stream << line;
        }
        return input_stream.str();
    }
};
