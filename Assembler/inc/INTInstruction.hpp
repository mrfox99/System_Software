#ifndef _INTInstruction_HPP_
#define _INTInstruction_HPP_

#include "Instruction.hpp"

class RegisterOperand;

class INTInstruction: public Instruction{
protected:
    RegisterOperand *registerOperand;
public:
    INTInstruction(RegisterOperand *registerOperand);
    virtual ~INTInstruction();
    virtual unsigned int getSize();
    virtual int generateMachineCode(Assembler *assembler);
    
};

#endif
