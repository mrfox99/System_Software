#include "../inc/PUSHInstruction.hpp"
#include "../inc/Assembler.hpp"
#include "../inc/MachineInstruction.hpp"
#include "../inc/RegisterArgument.hpp"
#include "../inc/RegisterOperand.hpp"
#include "../inc/Section.hpp"
#include "../inc/SymbolTableEntry.hpp"
#include "../inc/RelocationTableEntry.hpp"

PUSHInstruction::PUSHInstruction(RegisterOperand *registerOperand):
registerOperand(registerOperand){

}

PUSHInstruction::~PUSHInstruction(){
    delete registerOperand;
}

unsigned int PUSHInstruction::getSize(){
    return 3;
}

int PUSHInstruction::generateMachineCode(Assembler *assembler){

    MachineInstruction mi;

    std::string intstruction = 
                mi
            .setOperationCode(MachineInstruction::OperationCode::STR)
            .setDesitnationRegister(MachineInstruction::getRegister(
                registerOperand->getRegisterArgument()->getValue()))
            .setSourceRegister(MachineInstruction::Register::SP)
            .setUpdateMode(MachineInstruction::UpdateMode::PRE_DECREMENT)
            .setAddressMode(MachineInstruction::AddressMode::REGISTER_INDIRECT)
            .getInstruction();
    
    assembler->getActiveSection()->machineCode += intstruction;
    assembler->getActiveSection()->counter += getSize();
    return 0;
}