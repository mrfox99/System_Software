#ifndef _MemorySymbolOperand_HPP_
#define _MemorySymbolOperand_HPP_

#include "Operand.hpp"

class SymbolArgument;

class MemorySymbolOperand: public Operand{

protected:
    SymbolArgument *symbolArgument;

public:
    MemorySymbolOperand(SymbolArgument *symbolArgument);
    virtual ~MemorySymbolOperand();
    virtual std::string getType();
    virtual std::vector<OperandArgument*> getArguments();
    SymbolArgument* getSymbolArgument();
};

#endif
