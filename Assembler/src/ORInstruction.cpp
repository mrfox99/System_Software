#include "../inc/ORInstruction.hpp"

ORInstruction::ORInstruction(
        RegisterOperand *registerOperandDestination, 
        RegisterOperand *registerOperandSource)
:RegisterRegisterInstruction(
    registerOperandDestination, 
    registerOperandSource){

}

ORInstruction::~ORInstruction(){

}

MachineInstruction::OperationCode ORInstruction::getOperationCode(){
    return MachineInstruction::OperationCode::OR;
}
