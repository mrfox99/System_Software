#include "../inc/LDRInstruction.hpp"

LDRInstruction::LDRInstruction(
    RegisterOperand *registerOperand, 
    Operand *operand)
:RegisterOperandInstruction(registerOperand, operand){

}

LDRInstruction::~LDRInstruction(){

}

MachineInstruction::OperationCode LDRInstruction::getOperationCode(){
    return MachineInstruction::OperationCode::LDR;
}
