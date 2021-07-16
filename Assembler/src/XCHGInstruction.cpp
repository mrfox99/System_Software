#include "../inc/XCHGInstruction.hpp"

XCHGInstruction::XCHGInstruction(
        RegisterOperand *registerOperandDestination, 
        RegisterOperand *registerOperandSource)
:RegisterRegisterInstruction(
    registerOperandDestination, 
    registerOperandSource){

}

XCHGInstruction::~XCHGInstruction(){

}

MachineInstruction::OperationCode XCHGInstruction::getOperationCode(){
    return MachineInstruction::OperationCode::XCHG;
}
