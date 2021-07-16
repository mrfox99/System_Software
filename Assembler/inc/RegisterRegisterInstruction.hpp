#ifndef _RegisterRegisterInstruction_HPP_
#define _RegisterRegisterInstruction_HPP_

#include "Instruction.hpp"
#include "MachineInstruction.hpp"

class RegisterOperand;

class RegisterRegisterInstruction: public Instruction{
    
protected:
    RegisterOperand *registerOperandDestination;
    RegisterOperand *registerOperandSource;

public:
    RegisterRegisterInstruction(
        RegisterOperand *registerOperandDestination, 
        RegisterOperand *registerOperandSource);
    virtual ~RegisterRegisterInstruction();

    virtual unsigned int getSize();
    virtual int generateMachineCode(Assembler *assembler);
    virtual MachineInstruction::OperationCode getOperationCode() = 0;
};

#endif
