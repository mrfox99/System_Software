#include "../inc/NOTInstruction.hpp"
#include "../inc/Assembler.hpp"
#include "../inc/MachineInstruction.hpp"
#include "../inc/RegisterArgument.hpp"
#include "../inc/RegisterOperand.hpp"
#include "../inc/Section.hpp"
#include "../inc/SymbolTableEntry.hpp"
#include "../inc/RelocationTableEntry.hpp"

NOTInstruction::NOTInstruction(RegisterOperand *registerOperand):
registerOperand(registerOperand){

}

NOTInstruction::~NOTInstruction(){
    delete registerOperand;
}

unsigned int NOTInstruction::getSize(){
    return 2;
}

int NOTInstruction::generateMachineCode(Assembler *assembler){

    MachineInstruction mi;

    std::string intstruction = 
                mi
            .setOperationCode(MachineInstruction::OperationCode::NOT)
            .setDesitnationRegister(MachineInstruction::getRegister(
                registerOperand->getRegisterArgument()->getValue()))
            .getInstruction();
    
    assembler->getActiveSection()->machineCode += intstruction;
    assembler->getActiveSection()->counter += getSize();
    return 0;
}