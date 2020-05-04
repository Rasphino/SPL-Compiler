#include <iostream>
#include <cstdlib>
#include <cstring>

#include "Driver.hpp"

int main(const int argc, const char **argv) {
    if (argc == 2) {
        SPL::Driver driver;
        if (std::strncmp(argv[1], "-o", 2) == 0) {
            driver.parse(std::cin);
        } else if (std::strncmp(argv[1], "-h", 2) == 0) {
            std::cout << "use -o for pipe to std::cin\n";
            std::cout << "just give a filename to count from a file\n";
            std::cout << "use -h to get this menu\n";
            return (EXIT_SUCCESS);
        } else {
            driver.parse(argv[1]);
        }
        driver.print(std::cout) << "\n";
    } else {
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
