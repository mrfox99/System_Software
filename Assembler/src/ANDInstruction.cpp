#include "../inc/ANDInstruction.hpp"

ANDInstruction::ANDInstruction(
        RegisterOperand *registerOperandDestination, 
        RegisterOperand *registerOperandSource)
:RegisterRegisterInstruction(
    registerOperandDestination, 
    registerOperandSource){

}

ANDInstruction::~ANDInstruction(){

}

MachineInstruction::OperationCode ANDInstruction::getOperationCode(){
    return MachineInstruction::OperationCode::AND;
}
