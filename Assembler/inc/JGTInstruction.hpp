#ifndef _JGTInstruction_HPP_
#define _JGTInstruction_HPP_

#include "OperandInstruction.hpp"
#include "MachineInstruction.hpp"

class Operand;

class JGTInstruction: public OperandInstruction{

public:
    JGTInstruction(Operand *operand);
    virtual ~JGTInstruction();
    MachineInstruction::OperationCode getOperationCode();
    
};

#endif
