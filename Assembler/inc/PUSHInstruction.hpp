#ifndef _PUSHInstruction_HPP_
#define _PUSHInstruction_HPP_

#include "Instruction.hpp"

class RegisterOperand;

class PUSHInstruction: public Instruction{
protected:
    RegisterOperand *registerOperand;
public:
    PUSHInstruction(RegisterOperand *registerOperand);
    virtual ~PUSHInstruction();
    virtual unsigned int getSize();
    virtual int generateMachineCode(Assembler *assembler);
    
};

#endif
