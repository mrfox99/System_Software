#include "../inc/RegisterArgument.hpp"

RegisterArgument::RegisterArgument(char reg)
:reg(reg){
}

RegisterArgument::~RegisterArgument(){
}

bool RegisterArgument::isResolved(std::map<std::string,SymbolTableEntry*> *symbolTable){
    return true;
}
bool RegisterArgument::isDefined(std::map<std::string,SymbolTableEntry*> *symbolTable){
    return true;
}
short RegisterArgument::getValue(std::map<std::string,SymbolTableEntry*> *symbolTable){
    return reg;
}
SymbolTableEntry* RegisterArgument::getSymbol(std::map<std::string,SymbolTableEntry*> *symbolTable){
    return nullptr;
}
std::string RegisterArgument::getName(){
    return "r" + std::to_string(reg);
}