#include "../inc/JNEInstruction.hpp"

JNEInstruction::JNEInstruction(Operand *operand)
:OperandInstruction(operand){
    
}

JNEInstruction::~JNEInstruction(){
}


MachineInstruction::OperationCode JNEInstruction::getOperationCode(){
    return MachineInstruction::OperationCode::JNE;
}