#ifndef _SHLInstruction_HPP_
#define _SHLInstruction_HPP_

#include "RegisterRegisterInstruction.hpp"

class RegisterOperand;

class SHLInstruction: public RegisterRegisterInstruction{

public:
    SHLInstruction(
        RegisterOperand *registerOperandDestination, 
        RegisterOperand *registerOperandSource);
    virtual ~SHLInstruction();
    virtual MachineInstruction::OperationCode getOperationCode();
};

#endif
