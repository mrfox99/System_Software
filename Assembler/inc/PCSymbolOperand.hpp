#ifndef _PCSymbolOperand_HPP_
#define _PCSymbolOperand_HPP_

#include "Operand.hpp"

class SymbolArgument;

class PCSymbolOperand: public Operand{

protected:
    SymbolArgument *symbolArgument;
    
public:
    PCSymbolOperand(SymbolArgument *symbolArgument);
    virtual ~PCSymbolOperand();
    virtual std::string getType();
    virtual std::vector<OperandArgument*> getArguments();
    SymbolArgument* getSymbolArgument();
};

#endif
