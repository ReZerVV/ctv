#ifndef TABLE_H_
#define TABLE_H_

#include <stddef.h>
#include <string>
#include <vector>

enum cell_type : uint8_t {
    type_none,
    type_number,
    type_string,
    type_expresion,
};

std::string cell_type_to_string(const cell_type type);

class cell {
public:
    cell();
    cell(const cell_type type, const std::string &_value);
    cell(const cell &other);
    cell& operator=(const cell &other);
    ~cell();
public:
    cell_type _type;
    std::string _value;
};

class parser {
public:
    parser() = default;
    parser(const parser &other) = default;
    parser& operator=(const parser &other) = default;
    ~parser() = default;
public:
    bool end() const;
    void set(const std::string &source);
    cell next();
private:
    char peek(size_t offset);
    void advance();
    void skip();
    cell parse_value();
    cell parse_none();
public:
    std::string _source;
    size_t      _index;
    char        _sym;
};

class table {
public:
    friend void table_print(const table t);
public:
    table() = default;
    table(const table &other) = default;
    table& operator=(const table &other) = default;
    ~table() = default;
public:
    void csv(const std::string &file_path);
private:
    std::string _file;
    std::vector< std::vector< cell > > _data;
};

#endif // TABLE_H_