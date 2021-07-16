#ifndef _MemoryLiteralOperand_HPP_
#define _MemoryLiteralOperand_HPP_

#include "Operand.hpp"

class LiteralArgument;

class MemoryLiteralOperand: public Operand{

protected:
    LiteralArgument *literalArgument;

public:
    MemoryLiteralOperand(LiteralArgument *literalArgument);
    virtual ~MemoryLiteralOperand();
    virtual std::string getType();
    virtual std::vector<OperandArgument*> getArguments();
    LiteralArgument* getLiteralArgument();
};

#endif
