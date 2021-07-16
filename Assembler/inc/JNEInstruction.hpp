#ifndef _JNEInstruction_HPP_
#define _JNEInstruction_HPP_

#include "OperandInstruction.hpp"
#include "MachineInstruction.hpp"

class Operand;

class JNEInstruction: public OperandInstruction{

public:
    JNEInstruction(Operand *operand);
    virtual ~JNEInstruction();
    MachineInstruction::OperationCode getOperationCode();
    
};

#endif
