#include <iostream>
#include "table.hpp"
#include "renderer.hpp"

int main(int argc, char** argv) {
    if (argc <= 1) {
        std::cout << "File path is not found." << std::endl;
        return 1;
    }

    table t{  };
    t.csv(argv[1]);
    table_print(t);
    
    return 0;
}