#ifndef _ADDInstruction_HPP_
#define _ADDInstruction_HPP_

#include "RegisterRegisterInstruction.hpp"

class RegisterOperand;

class ADDInstruction: public RegisterRegisterInstruction{

public:
    ADDInstruction(
        RegisterOperand *registerOperandDestination, 
        RegisterOperand *registerOperandSource);
    virtual ~ADDInstruction();
    virtual MachineInstruction::OperationCode getOperationCode();
};

#endif
