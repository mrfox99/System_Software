#include "../inc/CALLInstruction.hpp"

CALLInstruction::CALLInstruction(Operand *operand)
:OperandInstruction(operand){
    
}

CALLInstruction::~CALLInstruction(){
}


MachineInstruction::OperationCode CALLInstruction::getOperationCode(){
    return MachineInstruction::OperationCode::CALL;
}