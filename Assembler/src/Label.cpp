#include <iostream>

#include "../inc/Label.hpp"
#include "../inc/Section.hpp"
#include "../inc/SymbolTableEntry.hpp"
#include "../inc/Assembler.hpp"

Label::Label(std::string name)
:name(name){

}

Label::~Label(){

}

unsigned int Label::getSize(){
    return 0;
}
int Label::updateSymbolTable(Assembler *assembler){

    auto iterator = assembler->getSymbolTable()->find(name);
    
    if(iterator != assembler->getSymbolTable()->end()){
        if(!(*iterator).second->defined){
            (*iterator).second->value = assembler->getActiveSection()->counter;
            (*iterator).second->defined = true;
            if((*iterator).second->scope == "Extern")
                (*iterator).second->scope = "Local";
            (*iterator).second->type = "Relocatable";
            (*iterator).second->section = assembler->getActiveSection();
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
                name, 
                new SymbolTableEntry{
                    name,
                    (unsigned short)assembler->getActiveSection()->counter,
                    "Local",
                    "Relocatable",
                    true,
                    assembler->getActiveSection()
                }
            )
        );
        return 0;
    }
}
int Label::generateMachineCode(Assembler *assembler){
    return 0;
}