#include "../inc/TESTInstruction.hpp"

TESTInstruction::TESTInstruction(
        RegisterOperand *registerOperandDestination, 
        RegisterOperand *registerOperandSource)
:RegisterRegisterInstruction(
    registerOperandDestination, 
    registerOperandSource){

}

TESTInstruction::~TESTInstruction(){

}

MachineInstruction::OperationCode TESTInstruction::getOperationCode(){
    return MachineInstruction::OperationCode::TEST;
}
