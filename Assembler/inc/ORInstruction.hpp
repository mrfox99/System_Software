#ifndef _ORInstruction_HPP_
#define _ORInstruction_HPP_

#include "RegisterRegisterInstruction.hpp"

class RegisterOperand;

class ORInstruction: public RegisterRegisterInstruction{

public:
    ORInstruction(
        RegisterOperand *registerOperandDestination, 
        RegisterOperand *registerOperandSource);
    virtual ~ORInstruction();
    virtual MachineInstruction::OperationCode getOperationCode();
};

#endif
