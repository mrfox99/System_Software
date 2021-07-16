#ifndef _ExternDirective_HPP_
#define _ExternDirective_HPP_

#include "Directive.hpp"

class SymbolOperand;

class ExternDirective: public Directive{
    
protected:
    std::vector<SymbolOperand*> symbolOperands;
public:
    ExternDirective(std::vector<SymbolOperand*> symbolOperands);
    virtual ~ExternDirective();

    virtual unsigned int getSize();
    virtual int updateSymbolTable(Assembler *assembler);
    virtual int generateMachineCode(Assembler *assembler);
};




#endif