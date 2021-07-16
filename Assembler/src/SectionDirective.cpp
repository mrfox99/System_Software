#include "../inc/SectionDirective.hpp"
#include "../inc/Assembler.hpp"
#include "../inc/Section.hpp"
#include "../inc/SymbolTableEntry.hpp"
#include "../inc/SymbolOperand.hpp"
#include "../inc/SymbolArgument.hpp"

#include <iostream>

SectionDirective::SectionDirective(SymbolOperand *symbolOperand)
:symbolOperand(symbolOperand){
}

SectionDirective::~SectionDirective(){
    delete symbolOperand;
}

unsigned int SectionDirective::getSize(){
    return 0;
}

int SectionDirective::updateSymbolTable(Assembler *assembler){

    Section *section = nullptr;
    if(!symbolOperand->getSymbolArgument()->isResolved(assembler->getSymbolTable())){
        SymbolTableEntry *symbolTableEntry = new SymbolTableEntry{
                                                        symbolOperand->getSymbolArgument()->getName(),
                                                        0,
                                                        "Global",
                                                        "Relocatable",
                                                        true,
                                                        nullptr
                                                        };
        assembler->getSymbolTable()->insert(
            std::pair<std::string,SymbolTableEntry*>(symbolTableEntry->name, symbolTableEntry));

        section = new Section{
                                symbolTableEntry, 
                                0, 
                                ""
                                };
        assembler->getSectionTable()->insert(std::pair<std::string, Section*>(symbolTableEntry->name, section));
        symbolTableEntry->section = section;
        assembler->setActiveSection(section);

        return 0;
    }
    else if(!symbolOperand->getSymbolArgument()->isDefined(assembler->getSymbolTable())){
        SymbolTableEntry *symbolTableEntry = symbolOperand->getSymbolArgument()->getSymbol(assembler->getSymbolTable());

        symbolTableEntry->value = assembler->getActiveSection()->counter;
        symbolTableEntry->defined = true;
        symbolTableEntry->scope = "Global";
        symbolTableEntry->type = "Relocatable";
        symbolTableEntry->section = assembler->getActiveSection();

        section = new Section{
                                symbolTableEntry, 
                                0, 
                                ""
                                };
        assembler->getSectionTable()->insert(std::pair<std::string, Section*>(symbolTableEntry->name, section));

        symbolTableEntry->section = section;
        return 0;
    }
    else if(symbolOperand->getSymbolArgument()->getSymbol(assembler->getSymbolTable()) == 
        symbolOperand->getSymbolArgument()->getSymbol(assembler->getSymbolTable())->section->symbol){
            section = symbolOperand->getSymbolArgument()->getSymbol(assembler->getSymbolTable())->section;
        return 0;
    }
    else{
        std::cout << "Multiple definition of symbol" << std::endl;
        return -1;
    }
}
int SectionDirective::generateMachineCode(Assembler *assembler){

    assembler->setActiveSection(
        assembler->getSectionTable()->find(symbolOperand->getArguments()[0]->getName())->second
        );
    return 0;        
}