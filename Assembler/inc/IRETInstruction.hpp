#ifndef _IRETInstruction_HPP_
#define _IRETInstruction_HPP_

#include "NoOperandInstruction.hpp"


class IRETInstruction: public NoOperandInstruction{

public:
    IRETInstruction();
    virtual ~IRETInstruction();
    virtual MachineInstruction::OperationCode getOperationCode();
    
};

#endif
