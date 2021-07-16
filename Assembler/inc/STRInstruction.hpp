#ifndef _STRInstruction_HPP_
#define _STRInstruction_HPP_

#include "RegisterOperandInstruction.hpp"

class RegisterOperand;

class STRInstruction: public RegisterOperandInstruction{

public:
    STRInstruction(
        RegisterOperand *registerOperand, 
        Operand *operand);
    virtual ~STRInstruction();
    virtual MachineInstruction::OperationCode getOperationCode();
};

#endif
