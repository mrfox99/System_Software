#include "../inc/SHLInstruction.hpp"

SHLInstruction::SHLInstruction(
        RegisterOperand *registerOperandDestination, 
        RegisterOperand *registerOperandSource)
:RegisterRegisterInstruction(
    registerOperandDestination, 
    registerOperandSource){

}

SHLInstruction::~SHLInstruction(){

}

MachineInstruction::OperationCode SHLInstruction::getOperationCode(){
    return MachineInstruction::OperationCode::SHL;
}
