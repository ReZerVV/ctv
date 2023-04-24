#include "table.hpp"
#include <fstream>
#include <iostream>

std::string cell_type_to_string(const cell_type type) {
    switch (type) {
    case cell_type::type_none: return "cell_type::type_none";
    case cell_type::type_number: return "cell_type::type_number";
    case cell_type::type_string: return "cell_type::type_string";
    case cell_type::type_expresion: return "cell_type::type_expresion";
    default: return "default";
    }
}

// Cell.
cell::cell()
    :
    _type(cell_type::type_none) {}

cell::cell(const cell_type type, const std::string &value)
    :
    _type(type),
    _value(value) {}

cell::cell(const cell &other)
    : 
    _type(other._type),
    _value(other._value) {}

cell& cell::operator=(const cell &other) {
    _type = other._type;
    _value = other._value;
    return *this;
}

cell::~cell() {}

// Parser.
#define delimiter ','

bool parser::end() const { 
    return _sym == '\0' || _sym == '\r';
}

void parser::set(const std::string &source) {
    _source = source;
    _index = 0;
    _sym = _source[_index];
}

cell parser::next() {
    while (_sym != '\0') {
        skip();

        if (_sym != delimiter)  { return parse_value(); }
        if (_sym == delimiter)  { return parse_none(); }
    }
}

char parser::peek(size_t offset) {
    if (_index + offset < _source.size()) {
        return _source[_index + offset];
    }
    return '\0';
}

void parser::advance() {
    if (_sym != '\0' && _index < _source.size()) {
        _index += 1;
        _sym = _source[_index];
    }
}

void parser::skip() {
    while (isspace(_sym)) {
        advance();
    }
}

cell parser::parse_value() {
    cell _cell{  };

    char temp[] = {'0', '\0'};
    char delim = delimiter;
    if (_sym == '"') {
        advance();
        while (_sym != '"' && _sym != '\0') {
            temp[0] = _sym;
            _cell._value.append(temp);
            advance();
            if (_sym == '"' && peek(1) == '"') {
               advance();
               _cell._value.append("\"");
               advance(); 
            }
        }
        advance();
        advance();
    } else {
        while (_sym != delimiter && _sym != '\0') {
            temp[0] = _sym;
            _cell._value.append(temp);
            advance();
        }
        advance();
    }

    return _cell;
}

cell parser::parse_none() {
    advance();
    return cell{  };
}

// Table.
void table::csv(const std::string &file_path) {
    _file = file_path;
    parser _parser{ };
    _data.clear();
    
    std::ifstream file;
    file.open(file_path);
    if (!file.is_open()) {
        std::cout << "File is not found" << std::endl;
        return;
    }
    
    std::string line_data;
    for (size_t y = 0; file.good(); ++y) {
        std::getline(file, line_data);
        _parser.set(line_data);
        _data.push_back(std::vector<cell>{  });
        while (!_parser.end()) {
            _data[y].push_back(_parser.next());
        }
        line_data.clear();
    }
    
    file.close();
}