#include "../inc/SymbolArgument.hpp"
#include "../inc/SymbolTableEntry.hpp"
#include <iostream>

SymbolArgument::SymbolArgument(std::string name)
:name(name){

}

SymbolArgument::~SymbolArgument(){

}

bool SymbolArgument::isResolved(std::map<std::string, SymbolTableEntry*> *symbolTable){
    return symbolTable->find(name) != symbolTable->end();

}

bool SymbolArgument::isDefined(std::map<std::string, SymbolTableEntry*> *symbolTable){
    return symbolTable->find(name)->second->defined;
}

short SymbolArgument::getValue(std::map<std::string,SymbolTableEntry*> *symbolTable){
    return symbolTable->find(name)->second->value;
}

SymbolTableEntry* SymbolArgument::getSymbol(std::map<std::string,SymbolTableEntry*> *symbolTable){
    return symbolTable->find(name)->second;
}

std::string SymbolArgument::getName(){
    return name;
}