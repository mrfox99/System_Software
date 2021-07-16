#ifndef _WordDirective_HPP_
#define _WordDirective_HPP_

#include "Directive.hpp"

class Operand;

class WordDirective: public Directive{
    
protected:
    std::vector<Operand*> operands;
public:
    WordDirective(std::vector<Operand*> operands);
    virtual ~WordDirective();

    virtual unsigned int getSize();
    virtual int updateSymbolTable(Assembler *assembler);
    virtual int generateMachineCode(Assembler *assembler);
};




#endif