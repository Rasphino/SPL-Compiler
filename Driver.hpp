#ifndef TINY_COMPILER_DRIVER_H
#define TINY_COMPILER_DRIVER_H

#include <string>
#include <cstddef>
#include <istream>

#include "tiny_scanner.hpp"
#include "tiny_parser.tab.hh"

namespace TINY {

    class Driver {
    public:
        Driver() = default;

        virtual ~Driver();

        /**
         * parse - parse from a file
         * @param filename - valid string with input file
         */
        void parse(const char *const filename);

        /**
         * parse - parse from a c++ input stream
         * @param is - std::istream&, valid input stream
         */
        void parse(std::istream &iss);

        void add_upper();
        void add_lower();
        void add_word(const std::string &word);
        void add_newline();
        void add_char();

        std::ostream &print(std::ostream &stream);


    private:
        void parse_helper(std::istream &stream);

        std::size_t chars = 0;
        std::size_t words = 0;
        std::size_t lines = 0;
        std::size_t uppercase = 0;
        std::size_t lowercase = 0;
        TINY::Parser *parser = nullptr;
        TINY::Scanner *scanner = nullptr;

        const std::string red = "\033[1;31m";
        const std::string blue = "\033[1;36m";
        const std::string norm = "\033[0m";
    };

} /* end namespace TINY */
#endif
