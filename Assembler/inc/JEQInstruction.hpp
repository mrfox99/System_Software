#ifndef _JEQInstruction_HPP_
#define _JEQInstruction_HPP_

#include "OperandInstruction.hpp"
#include "MachineInstruction.hpp"

class Operand;

class JEQInstruction: public OperandInstruction{

public:
    JEQInstruction(Operand *operand);
    virtual ~JEQInstruction();
    MachineInstruction::OperationCode getOperationCode();
    
};

#endif
