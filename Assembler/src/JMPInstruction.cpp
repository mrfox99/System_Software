#include "../inc/JMPInstruction.hpp"

JMPInstruction::JMPInstruction(Operand *operand)
:OperandInstruction(operand){
    
}

JMPInstruction::~JMPInstruction(){
}


MachineInstruction::OperationCode JMPInstruction::getOperationCode(){
    return MachineInstruction::OperationCode::JMP;
}