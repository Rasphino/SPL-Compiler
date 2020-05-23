%{
// TODO
#include <iostream>
#include <string>

int line_cnt = 1;
%}

delim       [ \t]
ws          {delim}+
letter      [a-zA-Z]
digit       [0-9]
id          {letter}(_|{letter}|{digit})*
integer     {digit}+
real        {digit}+(\.{digit}+)?(([E|e])[+\-]?{digit}+)?
/* comment1    ("{") */
/* comment2    (\/\/.*\n) */
string      [\']

A [Aa]
B [Bb]
C [Cc]
D [Dd]
E [Ee]
F [Ff]
G [Gg]
H [Hh]
I [Ii]
J [Jj]
K [Kk]
L [Ll]
M [Mm]
N [Nn]
O [Oo]
P [Pp]
Q [Qq]
R [Rr]
S [Ss]
T [Tt]
U [Uu]
V [Vv]
W [Ww]
X [Xx]
Y [Yy]
Z [Zz]

%%
{ws}        {}
"\n"        { line_cnt++; }

"("         {}
")"         {}
"["         {}
"]"         {}
".."        {}
","         {}
":"         {}
";"         {}

"."         {}
"+"         {}
"-"         {}
"*"         {}
"<"         {}
"<="        {}
"="         {}
"<>"        {}
">"         {}
">="        {}
":="        {}

{A}{N}{D}            {}
{O}{R}               {}
{N}{O}{T}            {}
{D}{I}{V}|"/"        {}
{M}{O}{D}|"%"        {}

{A}{R}{R}{A}{Y}              {}
{B}{E}{G}{I}{N}              {}
{C}{A}{S}{E}                 {}
{C}{O}{N}{S}{T}              {}
{D}{O}                       {}
{D}{O}{W}{N}{T}{O}           {}
{E}{L}{S}{E}                 {}
{E}{N}{D}                    {}
{F}{O}{R}                    {}
{F}{U}{N}{C}{T}{I}{O}{N}     {}
{G}{O}{T}{O}                 {}
{I}{F}                       {}
{I}{N}                       {}
{O}{F}                       {}
{P}{A}{C}{K}{E}{D}           {}
{P}{R}{O}{C}{E}{D}{U}{R}{E}  {}
{P}{R}{O}{G}{R}{A}{M}        {}
{R}{E}{C}{O}{R}{D}           {}
{R}{E}{P}{E}{A}{T}           {}
{S}{E}{T}                    {}
{T}{H}{E}{N}                 {}
{T}{O}                       {}
{T}{Y}{P}{E}                 {}
{U}{N}{T}{I}{L}              {}
{V}{A}{R}                    {}
{W}{H}{I}{L}{E}              {}
{W}{I}{T}{H}                 {}

true|false|maxint           {}
abs|chr|odd|ord|pred|sqr|succ           {}
write|writeln           {}
boolean|char|integer|real|string        {}
read        {}

{id}        {}
{string}    {}
{integer}   {}
{real}      {}

.   { std::cerr << "Illegal token: " << yytext << " in line: " << line_cnt << std::endl; }
%%
