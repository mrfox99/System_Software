#include "../inc/ADDInstruction.hpp"

ADDInstruction::ADDInstruction(
        RegisterOperand *registerOperandDestination, 
        RegisterOperand *registerOperandSource)
:RegisterRegisterInstruction(
    registerOperandDestination, 
    registerOperandSource){

}

ADDInstruction::~ADDInstruction(){

}

MachineInstruction::OperationCode ADDInstruction::getOperationCode(){
    return MachineInstruction::OperationCode::ADD;
}
