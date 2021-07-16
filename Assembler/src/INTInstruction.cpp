#include "../inc/INTInstruction.hpp"
#include "../inc/Assembler.hpp"
#include "../inc/MachineInstruction.hpp"
#include "../inc/RegisterArgument.hpp"
#include "../inc/RegisterOperand.hpp"
#include "../inc/Section.hpp"
#include "../inc/SymbolTableEntry.hpp"
#include "../inc/RelocationTableEntry.hpp"

INTInstruction::INTInstruction(RegisterOperand *registerOperand):
registerOperand(registerOperand){

}

INTInstruction::~INTInstruction(){
    delete registerOperand;
}

unsigned int INTInstruction::getSize(){
    return 2;
}

int INTInstruction::generateMachineCode(Assembler *assembler){

    MachineInstruction mi;

    std::string intstruction = 
                mi
            .setOperationCode(MachineInstruction::OperationCode::INT)
            .setDesitnationRegister(MachineInstruction::getRegister(
                registerOperand->getRegisterArgument()->getValue()))
            .getInstruction();
    
    assembler->getActiveSection()->machineCode += intstruction;
    assembler->getActiveSection()->counter += getSize();
    return 0;
}