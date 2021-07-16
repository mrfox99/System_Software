#include "../inc/MULInstruction.hpp"

MULInstruction::MULInstruction(
        RegisterOperand *registerOperandDestination, 
        RegisterOperand *registerOperandSource)
:RegisterRegisterInstruction(
    registerOperandDestination, 
    registerOperandSource){

}

MULInstruction::~MULInstruction(){

}

MachineInstruction::OperationCode MULInstruction::getOperationCode(){
    return MachineInstruction::OperationCode::MUL;
}
