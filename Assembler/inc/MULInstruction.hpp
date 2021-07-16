#ifndef _MULInstruction_HPP_
#define _MULInstruction_HPP_

#include "RegisterRegisterInstruction.hpp"

class RegisterOperand;

class MULInstruction: public RegisterRegisterInstruction{

public:
    MULInstruction(
        RegisterOperand *registerOperandDestination, 
        RegisterOperand *registerOperandSource);
    virtual ~MULInstruction();
    virtual MachineInstruction::OperationCode getOperationCode();
};

#endif
