#include "../inc/RegisterOperandInstruction.hpp"
#include "../inc/Assembler.hpp"
#include "../inc/RegisterOperand.hpp"
#include "../inc/RegisterArgument.hpp"
#include "../inc/Section.hpp"
#include "../inc/SymbolTableEntry.hpp"
#include "../inc/RelocationTableEntry.hpp"

#include <iostream>

RegisterOperandInstruction::RegisterOperandInstruction(
    RegisterOperand *registerOperand, 
    Operand *operand)
:registerOperand(registerOperand), OperandInstruction(operand){
}

RegisterOperandInstruction::~RegisterOperandInstruction(){
    delete registerOperand;
    delete operand;
}

int RegisterOperandInstruction::generateMachineCode(Assembler *assembler){

    MachineInstruction mi = getMachineInstruction(assembler);

    mi.setDesitnationRegister(
        MachineInstruction::getRegister(
            registerOperand->getRegisterArgument()->getValue()
        )
    );
    
    std::string intstruction = mi.getInstruction();

    assembler->getActiveSection()->machineCode += intstruction;
    assembler->getActiveSection()->counter += getSize();
    return 0;
}