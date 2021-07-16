#include "../inc/Instruction.hpp"
#include "../inc/Operand.hpp"
#include "../inc/Section.hpp"
#include "../inc/Assembler.hpp"

Instruction::Instruction(){

}

Instruction::~Instruction(){

}

int Instruction::updateSymbolTable(Assembler* assembler){
    assembler->getActiveSection()->counter += getSize();
    return 0;
}
