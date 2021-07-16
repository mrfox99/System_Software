#ifndef _SectionDirective_HPP_
#define _SectionDirective_HPP_

#include <string>

#include "Directive.hpp"

class SymbolOperand;

class SectionDirective: public Directive{
protected:
    SymbolOperand* symbolOperand;
public:
    SectionDirective(SymbolOperand *symbolOperand);
    virtual ~SectionDirective();

    virtual unsigned int getSize();
    virtual int updateSymbolTable(Assembler *assembler);
    virtual int generateMachineCode(Assembler *assembler);
};

#endif
