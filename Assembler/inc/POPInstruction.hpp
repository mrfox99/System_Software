#ifndef _POPInstruction_HPP_
#define _POPInstruction_HPP_

#include "Instruction.hpp"

class RegisterOperand;

class POPInstruction: public Instruction{
protected:
    RegisterOperand *registerOperand;
public:
    POPInstruction(RegisterOperand *registerOperand);
    virtual ~POPInstruction();
    virtual unsigned int getSize();
    virtual int generateMachineCode(Assembler *assembler);
    
};

#endif
