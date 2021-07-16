#include "../inc/XORInstruction.hpp"

XORInstruction::XORInstruction(
        RegisterOperand *registerOperandDestination, 
        RegisterOperand *registerOperandSource)
:RegisterRegisterInstruction(
    registerOperandDestination, 
    registerOperandSource){

}

XORInstruction::~XORInstruction(){

}

MachineInstruction::OperationCode XORInstruction::getOperationCode(){
    return MachineInstruction::OperationCode::XOR;
}
