#ifndef _DIVInstruction_HPP_
#define _DIVInstruction_HPP_

#include "RegisterRegisterInstruction.hpp"

class RegisterOperand;

class DIVInstruction: public RegisterRegisterInstruction{

public:
    DIVInstruction(
        RegisterOperand *registerOperandDestination, 
        RegisterOperand *registerOperandSource);
    virtual ~DIVInstruction();
    virtual MachineInstruction::OperationCode getOperationCode();
};

#endif
