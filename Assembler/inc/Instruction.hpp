#ifndef _Instruction_HPP_
#define _Instruction_HPP_

#include <string>
#include <vector>

#include "Element.hpp"

class Assembler;

class Operand;

class Instruction: public Element{

public:
    Instruction();
    virtual ~Instruction() = 0;
    
    virtual int updateSymbolTable(Assembler* assembler);
};

#endif
