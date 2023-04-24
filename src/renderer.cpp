#include "renderer.hpp"
#include <iostream>
#include <iomanip>

void table_print(const table t) {
    if (t._data.empty()) {
        return;
    }
    //std::cout << "File: " << t._file << std::endl;
    for (size_t y = 0; y < t._data.size(); ++y) {
        for (size_t x = 0; x < t._data[y].size(); ++x) {
            size_t max_size = 0;
            for (size_t dy = 0; dy < t._data.size(); ++dy) {
                if (t._data[dy][x]._value.size() > max_size) {
                    max_size = t._data[dy][x]._value.size();
                }
            }
            std::cout << std::setw(max_size) << std::setfill(' ') << std::left << t._data[y][x]._value << '|';
        }
        std::cout << std::endl;
    }
}