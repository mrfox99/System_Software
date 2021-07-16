#ifndef _EndDirective_HPP_
#define _EndDirective_HPP_

#include "Directive.hpp"

class Assembler;

class EndDirective: public Directive{
    
protected:

public:
    EndDirective();
    virtual ~EndDirective();

    virtual unsigned int getSize();
    virtual int updateSymbolTable(Assembler *assembler);
    virtual int generateMachineCode(Assembler *assembler);
};

#endif