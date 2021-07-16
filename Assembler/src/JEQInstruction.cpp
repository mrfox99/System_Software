#include "../inc/JEQInstruction.hpp"

JEQInstruction::JEQInstruction(Operand *operand)
:OperandInstruction(operand){
    
}

JEQInstruction::~JEQInstruction(){
}


MachineInstruction::OperationCode JEQInstruction::getOperationCode(){
    return MachineInstruction::OperationCode::JEQ;
}