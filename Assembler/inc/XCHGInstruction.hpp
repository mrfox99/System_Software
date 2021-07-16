#ifndef _XCHGInstruction_HPP_
#define _XCHGInstruction_HPP_

#include "RegisterRegisterInstruction.hpp"

class RegisterOperand;

class XCHGInstruction: public RegisterRegisterInstruction{

public:
    XCHGInstruction(
        RegisterOperand *registerOperandDestination, 
        RegisterOperand *registerOperandSource);
    ~XCHGInstruction();
    virtual MachineInstruction::OperationCode getOperationCode();
};

#endif
