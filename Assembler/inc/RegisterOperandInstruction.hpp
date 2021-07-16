#ifndef _RegisterOperandInstruction_HPP_
#define _RegisterOperandInstruction_HPP_

#include "OperandInstruction.hpp"
#include "MachineInstruction.hpp"

class RegisterOperand;
class Operand;

class RegisterOperandInstruction: public OperandInstruction{
    
protected:
    RegisterOperand *registerOperand;

public:
    RegisterOperandInstruction(
        RegisterOperand *registerOperand, 
        Operand *operand);
    virtual ~RegisterOperandInstruction();

    virtual int generateMachineCode(Assembler *assembler);
    
    virtual MachineInstruction::OperationCode getOperationCode() = 0;
    //virtual std::string getType();
    
};

#endif
