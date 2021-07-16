#ifndef _RegisterIndirectOperand_HPP_
#define _RegisterIndirectOperand_HPP_

#include "Operand.hpp"

class RegisterArgument;

class RegisterIndirectOperand: public Operand{

protected:
    RegisterArgument* registerArgument;

public:
    RegisterIndirectOperand(RegisterArgument* registerArgument);
    virtual ~RegisterIndirectOperand();
    virtual std::string getType();
    virtual std::vector<OperandArgument*> getArguments();
    RegisterArgument* getRegisterArgument();
};

#endif