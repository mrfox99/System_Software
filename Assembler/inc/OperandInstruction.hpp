#ifndef _OperandInstruction_HPP_
#define _OperandInstruction_HPP_

#include "Instruction.hpp"
#include "MachineInstruction.hpp"

class Operand;

class OperandInstruction: public Instruction{
    
protected:
    Operand *operand;

public:
    OperandInstruction(Operand *operand);
    virtual ~OperandInstruction();

    virtual unsigned int getSize();
    virtual int generateMachineCode(Assembler *assembler);
    virtual MachineInstruction::OperationCode getOperationCode() = 0;
    virtual std::string getType();

protected:
    MachineInstruction getMachineInstruction(Assembler *assembler);
    
};

#endif
