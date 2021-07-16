#include "../inc/GlobalDirective.hpp"
#include "../inc/Assembler.hpp"
#include "../inc/Section.hpp"
#include "../inc/SymbolTableEntry.hpp"
#include "../inc/SymbolOperand.hpp"
#include "../inc/SymbolArgument.hpp"

GlobalDirective::GlobalDirective(std::vector<SymbolOperand*> symbolOperands)
:symbolOperands(symbolOperands){
}

GlobalDirective::~GlobalDirective(){
    for(auto symbolOperand: symbolOperands){
        delete symbolOperand;
    }
}

unsigned int GlobalDirective::getSize(){
    return 0;
}

int GlobalDirective::updateSymbolTable(Assembler *assembler){
    for(SymbolOperand *symbolOperand : symbolOperands){
        if(!symbolOperand->getSymbolArgument()->isResolved(assembler->getSymbolTable())){
            std::string name = symbolOperand->getSymbolArgument()->getName();
            assembler->getSymbolTable()->insert(
                std::pair<std::string, SymbolTableEntry*>(
                    name, 
                    new SymbolTableEntry{
                        name,
                        0,
                        "Global",
                        "Relocatable",
                        false,
                        nullptr
                    }
                )
            );
        }
        else{
            symbolOperand->getSymbolArgument()->getSymbol(assembler->getSymbolTable())->scope 
                = "Global";
        }
    }
    return 0;
}

int GlobalDirective::generateMachineCode(Assembler *assembler){
    return 0;
}