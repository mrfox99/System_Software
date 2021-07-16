#include "../inc/CMPInstruction.hpp"

CMPInstruction::CMPInstruction(
        RegisterOperand *registerOperandDestination, 
        RegisterOperand *registerOperandSource)
:RegisterRegisterInstruction(
    registerOperandDestination, 
    registerOperandSource){

}

CMPInstruction::~CMPInstruction(){

}

MachineInstruction::OperationCode CMPInstruction::getOperationCode(){
    return MachineInstruction::OperationCode::CMP;
}
