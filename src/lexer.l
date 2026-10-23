%{
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "ast.h"
#include "parser.hpp"

void yyerror(const char* s);
%}

%option noyywrap
%option yylineno

%%

[ \t\r]+                ; /* Ignore whitespace */
\n                      ; /* Handled by yylineno */

"//".*                  ; /* Line comment */
"/*"([^*]|\*+[^*/])*\*+"/" ; /* Block comment */

"int"                   { return KW_INT; }
"print"                 { return KW_PRINT; }
"if"                    { return KW_IF; }
"else"                  { return KW_ELSE; }

"=="                    { return OP_EQ; }
"!="                    { return OP_NEQ; }
"<="                    { return OP_LE; }
">="                    { return OP_GE; }
"<"                     { return OP_LT; }
">"                     { return OP_GT; }

"="                     { return '='; }
"+"                     { return '+'; }
"-"                     { return '-'; }
"*"                     { return '*'; }
"/"                     { return '/'; }
";"                     { return ';'; }
"{"                     { return '{'; }
"}"                     { return '}'; }
"("                     { return '('; }
")"                     { return ')'; }

[0-9]+                  {
                            yylval.int_val = std::atoi(yytext);
                            return NUMBER;
                        }

[a-zA-Z_][a-zA-Z0-9_]*  {
                            yylval.str_val = strdup(yytext);
                            return IDENTIFIER;
                        }

.                       {
                            std::cerr << "Lexical Error (line " << yylineno << "): Unexpected character '" << yytext[0] << "'\n";
                        }

%%
