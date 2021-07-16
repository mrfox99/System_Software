#include "../inc/JGTInstruction.hpp"

JGTInstruction::JGTInstruction(Operand *operand)
:OperandInstruction(operand){
    
}

JGTInstruction::~JGTInstruction(){
}


MachineInstruction::OperationCode JGTInstruction::getOperationCode(){
    return MachineInstruction::OperationCode::JGT;
}