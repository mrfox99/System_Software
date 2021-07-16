#include "../inc/SUBInstruction.hpp"

SUBInstruction::SUBInstruction(
        RegisterOperand *registerOperandDestination, 
        RegisterOperand *registerOperandSource)
:RegisterRegisterInstruction(
    registerOperandDestination, 
    registerOperandSource){

}

SUBInstruction::~SUBInstruction(){

}

MachineInstruction::OperationCode SUBInstruction::getOperationCode(){
    return MachineInstruction::OperationCode::SUB;
}
