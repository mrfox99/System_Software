#include "../inc/EquDirective.hpp"
#include "../inc/SymbolTableEntry.hpp"
#include "../inc/Assembler.hpp"
#include "../inc/SymbolOperand.hpp"
#include "../inc/LiteralOperand.hpp"
#include "../inc/SymbolArgument.hpp"
#include "../inc/LiteralArgument.hpp"

#include <iostream>

EquDirective::EquDirective(SymbolOperand *symbolOperand, LiteralOperand *literalOperand)
:symbolOperand(symbolOperand), literalOperand(literalOperand){
}

EquDirective::~EquDirective(){
    delete symbolOperand;
    delete literalOperand;
}

unsigned int EquDirective::getSize(){
    return 0;
}

int EquDirective::updateSymbolTable(Assembler *assembler){
    
    if(symbolOperand->getSymbolArgument()->isResolved(assembler->getSymbolTable())){
        SymbolTableEntry *ste = symbolOperand->getSymbolArgument()->getSymbol(assembler->getSymbolTable());
        if(!ste->defined){
            ste->value = literalOperand->getLiteralArgument()->getValue(assembler->getSymbolTable());
            ste->defined = true;
            if(ste->scope == "Extern")
                ste->scope = "Local";
            ste->type = "Absolute";
            ste->section = assembler->getActiveSection();
            return 0;
        }
        else{
            std::cout<<"Multiple definition of symbol" << std::endl;
            return -1;
        }
    }
    else{
        assembler->getSymbolTable()->insert(
            std::pair<std::string, SymbolTableEntry*>(
                symbolOperand->getSymbolArgument()->getName(), 
                new SymbolTableEntry{
                    symbolOperand->getSymbolArgument()->getName(),
                    (unsigned short)literalOperand->getLiteralArgument()->getValue(assembler->getSymbolTable()),
                    "Local",
                    "Absolute",
                    true,
                    assembler->getActiveSection()
                }
            )
        );
        return 0;
    }
}

int EquDirective::generateMachineCode(Assembler *assembler){
    return 0;
}