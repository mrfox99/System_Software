#include "../inc/ExternDirective.hpp"
#include "../inc/Assembler.hpp"
#include "../inc/SymbolTableEntry.hpp"
#include "../inc/SymbolOperand.hpp"
#include "../inc/SymbolArgument.hpp"

ExternDirective::ExternDirective(std::vector<SymbolOperand*> symbolOperands)
:symbolOperands(symbolOperands){
}

ExternDirective::~ExternDirective(){
    for(auto symbolOperand: symbolOperands){
        delete symbolOperand;
    }
}

unsigned int ExternDirective::getSize(){
    return 0;
}

int ExternDirective::updateSymbolTable(Assembler *assembler){
    
    for(SymbolOperand *symbolOperand : symbolOperands){
        if(!symbolOperand->getSymbolArgument()->isResolved(assembler->getSymbolTable())){
            std::string name = symbolOperand->getSymbolArgument()->getName();
            assembler->getSymbolTable()->insert(
                std::pair<std::string, SymbolTableEntry*>(
                    name, 
                    new SymbolTableEntry{
                        name,
                        0,
                        "Extern",
                        "Relocatable",
                        false,
                        nullptr
                    }
                )
            );
        }
    }
    return 0;
}

int ExternDirective::generateMachineCode(Assembler *assembler){
    return 0;
}