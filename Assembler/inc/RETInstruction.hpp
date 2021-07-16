#ifndef _RETInstruction_HPP_
#define _RETInstruction_HPP_

#include "NoOperandInstruction.hpp"


class RETInstruction: public NoOperandInstruction{

public:
    RETInstruction();
    virtual ~RETInstruction();
    virtual MachineInstruction::OperationCode getOperationCode();
    
};

#endif
