#ifndef _CALLInstruction_HPP_
#define _CALLInstruction_HPP_

#include "OperandInstruction.hpp"
#include "MachineInstruction.hpp"

class Operand;

class CALLInstruction: public OperandInstruction{

public:
    CALLInstruction(Operand *operand);
    virtual ~CALLInstruction();
    MachineInstruction::OperationCode getOperationCode();
    
};

#endif
