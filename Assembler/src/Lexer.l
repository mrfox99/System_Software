%{
#include <string>
#include <stdio.h>

#include "../inc/Nodes.hpp"

#include "Parser.hpp"

#define SAVE_IDENTIFIER yylval.string = new std::string(yytext, yyleng)
#define SAVE_HEX_NUMBER yylval.number = std::strtol(yytext, nullptr, 16)
#define SAVE_DEC_NUMBER yylval.number = std::strtol(yytext, nullptr, 10)
#define SAVE_REGISTER yylval.reg = std::strtol(yytext + 1, nullptr, 16)
#define SAVE_SP yylval.reg = 6
#define SAVE_PC yylval.reg = 7
#define SAVE_PSW yylval.reg = 8

extern "C" int yywrap(){
    return 1;
}
%}

%%

".global"               return GLOBAL;
".extern"               return EXTERN;
".section"              return SECTION;
".word"                 return WORD;
".skip"                 return SKIP;
".equ"                  return EQU;
".end"                  return END;
"halt"                  return HALT;
"int"                   return INT;
"iret"                  return IRET;
"call"                  return CALL;
"ret"                   return RET;
"jmp"                   return JMP;
"jeq"                   return JEQ;
"jne"                   return JNE;
"jgt"                   return JGT;
"push"                  return PUSH;
"pop"                   return POP;
"xchg"                  return XCHG;
"add"                   return ADD;
"sub"                   return SUB;
"mul"                   return MUL;
"div"                   return DIV;
"cmp"                   return CMP;
"not"                   return NOT;
"and"                   return AND;
"or"                    return OR;
"xor"                   return XOR;
"test"                  return TEST;
"shl"                   return SHL;
"shr"                   return SHR;
"ldr"                   return LDR;
"str"                   return STR;
"$"                     return DOLLAR;         
"*"                     return ASTERIX;
"%"                     return PERCENT;
"+"                     return PLUS;
"#"                     return HASH;
"["                     return LEFT_BRACKET;
"]"                     return RIGHT_BRACKET;
","                     return COMMA;
":"                     return COLON;
"\n"                    return END_LINE;
"sp"                    SAVE_SP; return REGISTER;
"pc"                    SAVE_PC; return REGISTER;
"psw"                   SAVE_PSW; return REGISTER;
#.*                     return COMMENT;
r[0-7]                  SAVE_REGISTER; return REGISTER;
0x[0-9A-F]+             SAVE_HEX_NUMBER; return NUMBER;
[0-9]+                  SAVE_DEC_NUMBER; return NUMBER;
[a-zA-Z_][a-zA-Z0-9_]*  SAVE_IDENTIFIER; return IDENTIFIER;
[ \t]+                  ;

%%