#ifndef _NoOperandInstruction_HPP_
#define _NoOperandInstruction_HPP_

#include "Instruction.hpp"
#include "MachineInstruction.hpp"

class Assembler;

class NoOperandInstruction: public Instruction{

public:
    NoOperandInstruction();
    virtual ~NoOperandInstruction();

    virtual unsigned int getSize();
    virtual int generateMachineCode(Assembler *assembler);
    
    virtual MachineInstruction::OperationCode getOperationCode() = 0;
};

#endif
