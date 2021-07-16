#include "../inc/STRInstruction.hpp"

STRInstruction::STRInstruction(
    RegisterOperand *registerOperand, 
    Operand *operand)
:RegisterOperandInstruction(registerOperand, operand){

}

STRInstruction::~STRInstruction(){

}

MachineInstruction::OperationCode STRInstruction::getOperationCode(){
    return MachineInstruction::OperationCode::STR;
}
