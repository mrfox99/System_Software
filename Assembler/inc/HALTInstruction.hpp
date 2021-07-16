#ifndef _HALTInstruction_HPP_
#define _HALTInstruction_HPP_

#include "NoOperandInstruction.hpp"


class HALTInstruction: public NoOperandInstruction{

public:
    HALTInstruction();
    virtual ~HALTInstruction();
    virtual MachineInstruction::OperationCode getOperationCode();
    
};

#endif
