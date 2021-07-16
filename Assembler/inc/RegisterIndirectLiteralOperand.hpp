#ifndef _RegisterIndirectLiteralOperand_HPP_
#define _RegisterIndirectLiteralOperand_HPP_

#include "Operand.hpp"

class RegisterArgument;
class LiteralArgument;

class RegisterIndirectLiteralOperand: public Operand{

protected:
    RegisterArgument* registerArgument;
    LiteralArgument *literalArgument;
    
public:
    RegisterIndirectLiteralOperand(
        RegisterArgument* registerArgument, 
        LiteralArgument *literalArgument);
    virtual ~RegisterIndirectLiteralOperand();
    virtual std::string getType();
    virtual std::vector<OperandArgument*> getArguments();
    RegisterArgument* getRegisterArgument();
    LiteralArgument* getLiteralArgument();
};

#endif
