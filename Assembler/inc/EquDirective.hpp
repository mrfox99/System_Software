#ifndef _EquDirective_HPP_
#define _EquDirective_HPP_

#include "Directive.hpp"

class Assembler;
class SymbolOperand;
class LiteralOperand;

class EquDirective: public Directive{
    
protected:
    SymbolOperand *symbolOperand;
    LiteralOperand *literalOperand;
public:
    EquDirective(SymbolOperand *symbolOperand, LiteralOperand *literalOperand);
    virtual ~EquDirective();

    virtual unsigned int getSize();
    virtual int updateSymbolTable(Assembler *assembler);
    virtual int generateMachineCode(Assembler *assembler);
};

#endif