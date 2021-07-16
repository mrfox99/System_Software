#ifndef _SymbolOperand_HPP_
#define _SymbolOperand_HPP_

#include "Operand.hpp"

class SymbolArgument;

class SymbolOperand: public Operand{

protected:
    SymbolArgument *symbolArgument;

public:
    SymbolOperand(SymbolArgument *symbolArgument);
    virtual ~SymbolOperand();
    virtual std::string getType();
    virtual std::vector<OperandArgument*> getArguments();
    SymbolArgument* getSymbolArgument();
};



#endif
