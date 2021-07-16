#include "../inc/DIVInstruction.hpp"

DIVInstruction::DIVInstruction(
        RegisterOperand *registerOperandDestination, 
        RegisterOperand *registerOperandSource)
:RegisterRegisterInstruction(
    registerOperandDestination, 
    registerOperandSource){

}

DIVInstruction::~DIVInstruction(){

}

MachineInstruction::OperationCode DIVInstruction::getOperationCode(){
    return MachineInstruction::OperationCode::DIV;
}
