#include <bitset>

#include "../inc/SkipDirective.hpp"
#include "../inc/Assembler.hpp"
#include "../inc/Section.hpp"
#include "../inc/SymbolTableEntry.hpp"
#include "../inc/LiteralOperand.hpp"
#include "../inc/LiteralArgument.hpp"

#include <iostream>

SkipDirective::SkipDirective(LiteralOperand *literalOperand)
:literalOperand(literalOperand){
}

SkipDirective::~SkipDirective(){
    delete literalOperand;
}

unsigned int SkipDirective::getSize(){
    return literalOperand->getArguments()[0]->getValue(nullptr);
}

int SkipDirective::updateSymbolTable(Assembler *assembler){
    return 0;
}

int SkipDirective::generateMachineCode(Assembler *assembler){
    std::string data = "";
            
    std::string tmp = "00000000";
    int n = literalOperand->getLiteralArgument()->getValue(assembler->getSymbolTable());
    for(int i = 0; i < n; i++)
        data += tmp;
        
    assembler->getActiveSection()->machineCode += data;
    assembler->getActiveSection()->counter += getSize();
    return 0;
}