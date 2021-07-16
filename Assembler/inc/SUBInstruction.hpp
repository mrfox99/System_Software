#ifndef _SUBInstruction_HPP_
#define _SUBInstruction_HPP_

#include "RegisterRegisterInstruction.hpp"

class RegisterOperand;

class SUBInstruction: public RegisterRegisterInstruction{

public:
    SUBInstruction(
        RegisterOperand *registerOperandDestination, 
        RegisterOperand *registerOperandSource);
    virtual ~SUBInstruction();
    virtual MachineInstruction::OperationCode getOperationCode();
};

#endif
