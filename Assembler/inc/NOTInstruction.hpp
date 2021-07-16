#ifndef _NOTInstruction_HPP_
#define _NOTInstruction_HPP_

#include "Instruction.hpp"

class Assembler;
class RegisterOperand;

class NOTInstruction: public Instruction{

protected:
    RegisterOperand *registerOperand;

public:
    NOTInstruction(RegisterOperand *registerOperand);
    virtual ~NOTInstruction();
    virtual unsigned int getSize();
    virtual int generateMachineCode(Assembler *assembler);
    
};

#endif
