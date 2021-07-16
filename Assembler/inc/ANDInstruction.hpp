#ifndef _ANDInstruction_HPP_
#define _ANDInstruction_HPP_

#include "RegisterRegisterInstruction.hpp"

class RegisterOperand;

class ANDInstruction: public RegisterRegisterInstruction{

public:
    ANDInstruction(
        RegisterOperand *registerOperandDestination, 
        RegisterOperand *registerOperandSource);
    virtual ~ANDInstruction();
    virtual MachineInstruction::OperationCode getOperationCode();
};

#endif
