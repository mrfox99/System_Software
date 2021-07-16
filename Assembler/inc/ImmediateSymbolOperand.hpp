#ifndef _ImmediateSymbolOperand_HPP_
#define _ImmediateSymbolOperand_HPP_

#include "Operand.hpp"

class SymbolArgument;

class ImmediateSymbolOperand: public Operand{

protected:
    SymbolArgument *symbolArgument;

public:
    ImmediateSymbolOperand(SymbolArgument *symbolArgument);
    virtual ~ImmediateSymbolOperand();
    virtual std::string getType();
    virtual std::vector<OperandArgument*> getArguments();
    SymbolArgument* getSymbolArgument();
};

#endif
