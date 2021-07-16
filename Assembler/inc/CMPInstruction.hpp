#ifndef _CMPInstruction_HPP_
#define _CMPInstruction_HPP_

#include "RegisterRegisterInstruction.hpp"

class RegisterOperand;

class CMPInstruction: public RegisterRegisterInstruction{

public:
    CMPInstruction(
        RegisterOperand *registerOperandDestination, 
        RegisterOperand *registerOperandSource);
    virtual ~CMPInstruction();
    virtual MachineInstruction::OperationCode getOperationCode();
};

#endif
