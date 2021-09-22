#pragma once

#include <vector>
#include <string>

#include "xor.h"

int CountLetters(const std::vector<uint8_t>& input) {
    int count = 0;
    for (size_t i = 0; i < input.size(); ++i) {
        if (std::isalpha(input[i])) {
            count++;
        }
    }
    return count;
}

class XorKeyFinder {
public:
    XorKeyFinder() {
        max_count_.push_back(-1);
        max_string_.push_back({});
    }

    ~XorKeyFinder() = default;

    void Search(const std::vector<uint8_t>& buffer) {
        uint16_t key = 0;
        std::vector<uint8_t> xord;
        int count = 0;
        while (key < 256) {
            xord = XorSingle(buffer, key);
            count = CountLetters(xord);
            if (count > max_count_.back()) {
                max_count_.push_back(count);
                max_string_.push_back(std::string(xord.begin(), xord.end()));
            }
            key++;
        }
    }

    std::string GetMaxLetterString() const {
        return max_string_.back();
    }

    int GetMaxLetterCount() const {
        return max_count_.back();
    }

    void Print() const {
        for (auto str : max_string_) {
            std::cout << "Max letter string " << str << std::endl;
        }
    }

private:
    std::vector<int> max_count_;
    std::vector<int> max_key_;
    std::vector<std::string> max_string_;
};
