#ifndef _JMPInstruction_HPP_
#define _JMPInstruction_HPP_

#include "OperandInstruction.hpp"
#include "MachineInstruction.hpp"

class Operand;

class JMPInstruction: public OperandInstruction{

public:
    JMPInstruction(Operand *operand);
    ~JMPInstruction();
    MachineInstruction::OperationCode getOperationCode();
    
};

#endif
