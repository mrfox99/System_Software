#ifndef _TESTInstruction_HPP_
#define _TESTInstruction_HPP_

#include "RegisterRegisterInstruction.hpp"

class RegisterOperand;

class TESTInstruction: public RegisterRegisterInstruction{

public:
    TESTInstruction(
        RegisterOperand *registerOperandDestination, 
        RegisterOperand *registerOperandSource);
    virtual ~TESTInstruction();
    virtual MachineInstruction::OperationCode getOperationCode();
};

#endif
