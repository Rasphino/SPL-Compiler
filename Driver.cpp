#include "Driver.hpp"

#include <cctype>
#include <fstream>
#include <cassert>

SPL::Driver::~Driver() {
    delete (scanner);
    scanner = nullptr;
    delete (parser);
    parser = nullptr;
}

void SPL::Driver::parse(const char *const filename) {
    assert(filename != nullptr);
    std::ifstream in_file(filename);
    if (!in_file.good()) {
        exit(EXIT_FAILURE);
    }
    parse_helper(in_file);
}

void SPL::Driver::parse(std::istream &stream) {
    if (!stream.good() && stream.eof()) {
        return;
    }
    parse_helper(stream);
}


void SPL::Driver::parse_helper(std::istream &stream) {
    delete (scanner);
    scanner = new SPL::Scanner(&stream);

    delete (parser);
    parser = new SPL::Parser((*scanner) /* scanner */,
                             (*this) /* driver */ );
    const int accept(0);
    if (parser->parse() != accept) {
        std::cerr << "Parse failed!!\n";
    }
}

void SPL::Driver::add_upper() {
    uppercase++;
    chars++;
    words++;
}

void SPL::Driver::add_lower() {
    lowercase++;
    chars++;
    words++;
}

void SPL::Driver::add_word(const std::string &word) {
    words++;
    chars += word.length();
    for (const char &c : word) {
        if (islower(c)) {
            lowercase++;
        } else if (isupper(c)) {
            uppercase++;
        }
    }
}

void SPL::Driver::add_newline() {
    lines++;
    chars++;
}

void SPL::Driver::add_char() {
    chars++;
}


std::ostream &SPL::Driver::print(std::ostream &stream) {
    stream << red << "Results: " << norm << "\n";
    stream << blue << "Uppercase: " << norm << uppercase << "\n";
    stream << blue << "Lowercase: " << norm << lowercase << "\n";
    stream << blue << "Lines: " << norm << lines << "\n";
    stream << blue << "Words: " << norm << words << "\n";
    stream << blue << "Characters: " << norm << chars << "\n";
    return (stream);
}
