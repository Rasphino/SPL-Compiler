#ifndef SPL_COMPILER_SPL_SCANNER_H
#define SPL_COMPILER_SPL_SCANNER_H

#if !defined(yyFlexLexerOnce)

#include <FlexLexer.h>

#endif

#include "SPL_parser.tab.hh"
#include "location.hh"

namespace SPL {

    class Scanner : public yyFlexLexer {
    public:

        Scanner(std::istream *in) : yyFlexLexer(in) {
        };

        virtual ~Scanner() {
        };

        //get rid of override virtual function warning
        using FlexLexer::yylex;

        virtual
        int yylex(SPL::Parser::semantic_type *const lval,
                  SPL::Parser::location_type *location);
        // YY_DECL defined in SPL_lexer.l
        // Method body created by flex in mc_lexer.yy.cc


    private:
        /* yyval ptr */
        SPL::Parser::semantic_type *yylval = nullptr;
    };

} /* end namespace SPL */

#endif
