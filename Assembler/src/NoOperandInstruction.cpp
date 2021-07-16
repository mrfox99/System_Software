#include "../inc/NoOperandInstruction.hpp"
#include "../inc/Assembler.hpp"
#include "../inc/Section.hpp"

NoOperandInstruction::NoOperandInstruction(){

}
NoOperandInstruction::~NoOperandInstruction(){
    
}

unsigned int NoOperandInstruction::getSize(){
    return 1;
}

int NoOperandInstruction::generateMachineCode(Assembler *assembler){

    MachineInstruction mi;

    std::string intstruction = 
                mi
            .setOperationCode(getOperationCode())
            .getInstruction();
    
    assembler->getActiveSection()->machineCode += intstruction;
    assembler->getActiveSection()->counter += getSize();
    return 0;
}