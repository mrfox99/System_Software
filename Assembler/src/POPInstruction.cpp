#include "../inc/POPInstruction.hpp"
#include "../inc/Assembler.hpp"
#include "../inc/MachineInstruction.hpp"
#include "../inc/RegisterArgument.hpp"
#include "../inc/RegisterOperand.hpp"
#include "../inc/Section.hpp"
#include "../inc/SymbolTableEntry.hpp"
#include "../inc/RelocationTableEntry.hpp"

POPInstruction::POPInstruction(RegisterOperand *registerOperand):
registerOperand(registerOperand){

}

POPInstruction::~POPInstruction(){
    delete registerOperand;
}

unsigned int POPInstruction::getSize(){
    return 3;
}

int POPInstruction::generateMachineCode(Assembler *assembler){

    MachineInstruction mi;

    std::string intstruction = 
                mi
            .setOperationCode(MachineInstruction::OperationCode::LDR)
            .setDesitnationRegister(MachineInstruction::getRegister(
                registerOperand->getRegisterArgument()->getValue()))
            .setSourceRegister(MachineInstruction::Register::SP)
            .setUpdateMode(MachineInstruction::UpdateMode::POST_INCREMENT)
            .setAddressMode(MachineInstruction::AddressMode::REGISTER_INDIRECT)
            .getInstruction();
    
    assembler->getActiveSection()->machineCode += intstruction;
    assembler->getActiveSection()->counter += getSize();
    return 0;
}