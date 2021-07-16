#ifndef _LiteralOperand_HPP_
#define _LiteralOperand_HPP_

#include "Operand.hpp"

class LiteralArgument;

class LiteralOperand: public Operand{

protected:
    LiteralArgument *literalArgument;

public:
    LiteralOperand(LiteralArgument *literalArgument);
    ~LiteralOperand();
    virtual std::string getType();
    virtual std::vector<OperandArgument*> getArguments();
    LiteralArgument* getLiteralArgument();
};



#endif
