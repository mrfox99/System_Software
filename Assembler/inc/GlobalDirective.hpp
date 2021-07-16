#ifndef _GlobalDirective_HPP_
#define _GlobalDirective_HPP_

#include "Directive.hpp"

class SymbolOperand;

class GlobalDirective: public Directive{
    
protected:
    std::vector<SymbolOperand*> symbolOperands;
public:
    GlobalDirective(std::vector<SymbolOperand*> symbolOperands);
    virtual ~GlobalDirective();

    virtual unsigned int getSize();
    virtual int updateSymbolTable(Assembler *assembler);
    virtual int generateMachineCode(Assembler *assembler);
};




#endif