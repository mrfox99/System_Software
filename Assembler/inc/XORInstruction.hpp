#ifndef _XORInstruction_HPP_
#define _XORInstruction_HPP_

#include "RegisterRegisterInstruction.hpp"

class RegisterOperand;

class XORInstruction: public RegisterRegisterInstruction{

public:
    XORInstruction(
        RegisterOperand *registerOperandDestination, 
        RegisterOperand *registerOperandSource);
    ~XORInstruction();
    virtual MachineInstruction::OperationCode getOperationCode();
};

#endif
