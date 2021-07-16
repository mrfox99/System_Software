#include "../inc/RegisterRegisterInstruction.hpp"
#include "../inc/Assembler.hpp"
#include "../inc/RegisterOperand.hpp"
#include "../inc/RegisterArgument.hpp"
#include "../inc/Section.hpp"

#include <iostream>

RegisterRegisterInstruction::RegisterRegisterInstruction(
    RegisterOperand *registerOperandDestination,
    RegisterOperand *registerOperandSource)
:registerOperandDestination(registerOperandDestination),
registerOperandSource(registerOperandSource){
}

RegisterRegisterInstruction::~RegisterRegisterInstruction(){
    delete registerOperandDestination;
    delete registerOperandSource;
}

unsigned int RegisterRegisterInstruction::getSize(){
    return 2;
}

int RegisterRegisterInstruction::generateMachineCode(Assembler *assembler){
    MachineInstruction mi;

    std::string intstruction = 
                mi
            .setOperationCode(getOperationCode())
            .setDesitnationRegister(MachineInstruction::getRegister(
                registerOperandDestination->getRegisterArgument()->getValue()))
            .setSourceRegister(MachineInstruction::getRegister(
                registerOperandSource->getRegisterArgument()->getValue()))
            .getInstruction();
    
    assembler->getActiveSection()->machineCode += intstruction;
    assembler->getActiveSection()->counter += getSize();
    return 0;
}