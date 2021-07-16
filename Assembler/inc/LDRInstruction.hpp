#ifndef _LDRInstruction_HPP_
#define _LDRInstruction_HPP_

#include "RegisterOperandInstruction.hpp"

class RegisterOperand;

class LDRInstruction: public RegisterOperandInstruction{

public:
    LDRInstruction(
        RegisterOperand *registerOperand, 
        Operand *operand);
    ~LDRInstruction();
    virtual MachineInstruction::OperationCode getOperationCode();
};

#endif
