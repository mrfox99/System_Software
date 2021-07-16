#ifndef _RegisterOperand_HPP_
#define _RegisterOperand_HPP_

#include "Operand.hpp"

class RegisterArgument;

class RegisterOperand: public Operand{

protected:
    RegisterArgument* registerArgument;

public:
    RegisterOperand(RegisterArgument* registerArgument);
    virtual ~RegisterOperand();
    virtual std::string getType();
    virtual std::vector<OperandArgument*> getArguments();
    RegisterArgument* getRegisterArgument();
};

#endif