#ifndef _ImmediateLiteralOperand_HPP_
#define _ImmediateLiteralOperand_HPP_

#include "Operand.hpp"

class LiteralArgument;

class ImmediateLiteralOperand: public Operand{

protected:
    LiteralArgument *literalArgument;

public:
    ImmediateLiteralOperand(LiteralArgument* literalArgument);
    virtual ~ImmediateLiteralOperand();
    virtual std::string getType();
    virtual std::vector<OperandArgument*> getArguments();
    LiteralArgument* getLiteralArgument();
};



#endif
