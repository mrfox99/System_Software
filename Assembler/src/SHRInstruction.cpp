#include "../inc/SHRInstruction.hpp"

SHRInstruction::SHRInstruction(
        RegisterOperand *registerOperandDestination, 
        RegisterOperand *registerOperandSource)
:RegisterRegisterInstruction(
    registerOperandDestination, 
    registerOperandSource){

}

SHRInstruction::~SHRInstruction(){

}

MachineInstruction::OperationCode SHRInstruction::getOperationCode(){
    return MachineInstruction::OperationCode::SHR;
}
