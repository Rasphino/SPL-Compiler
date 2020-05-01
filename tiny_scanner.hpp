#ifndef TINY_COMPILER_TINY_SCANNER_H
#define TINY_COMPILER_TINY_SCANNER_H

#if !defined(yyFlexLexerOnce)

#include <FlexLexer.h>

#endif

#include "tiny_parser.tab.hh"
#include "location.hh"

namespace TINY {

    class Scanner : public yyFlexLexer {
    public:

        Scanner(std::istream *in) : yyFlexLexer(in) {
        };

        virtual ~Scanner() {
        };

        //get rid of override virtual function warning
        using FlexLexer::yylex;

        virtual
        int yylex(TINY::Parser::semantic_type *const lval,
                  TINY::Parser::location_type *location);
        // YY_DECL defined in tiny_lexer.l
        // Method body created by flex in mc_lexer.yy.cc


    private:
        /* yyval ptr */
        TINY::Parser::semantic_type *yylval = nullptr;
    };

} /* end namespace TINY */

#endif
