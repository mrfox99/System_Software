#ifndef _RegisterIndirectSymbolOperand_HPP_
#define _RegisterIndirectSymbolOperand_HPP_

#include "Operand.hpp"

class RegisterArgument;
class SymbolArgument;

class RegisterIndirectSymbolOperand: public Operand{

protected:
    RegisterArgument* registerArgument; 
    SymbolArgument *symbolArgument;

public:
    RegisterIndirectSymbolOperand(
        RegisterArgument* registerArgument, 
        SymbolArgument *symbolArgument);
    virtual ~RegisterIndirectSymbolOperand();
    virtual std::string getType();
    virtual std::vector<OperandArgument*> getArguments();
    RegisterArgument* getRegisterArgument();
    SymbolArgument* getSymbolArgument();
    
};

#endif