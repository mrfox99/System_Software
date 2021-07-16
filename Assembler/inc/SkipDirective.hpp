#ifndef _SkipDirective_HPP_
#define _SkipDirective_HPP_

#include "Directive.hpp"

class LiteralOperand;

class SkipDirective: public Directive{
    
protected:
    LiteralOperand* literalOperand;
public:
    SkipDirective(LiteralOperand *literal_operand);
    virtual ~SkipDirective();

    virtual unsigned int getSize();
    virtual int updateSymbolTable(Assembler *assembler);
    virtual int generateMachineCode(Assembler *assembler);
};




#endif