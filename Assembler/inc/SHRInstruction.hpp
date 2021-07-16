#ifndef _SHRInstruction_HPP_
#define _SHRInstruction_HPP_

#include "RegisterRegisterInstruction.hpp"

class RegisterOperand;

class SHRInstruction: public RegisterRegisterInstruction{

public:
    SHRInstruction(
        RegisterOperand *registerOperandDestination, 
        RegisterOperand *registerOperandSource);
    virtual ~SHRInstruction();
    virtual MachineInstruction::OperationCode getOperationCode();
};

#endif
