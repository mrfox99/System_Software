#include "../inc/LiteralArgument.hpp"

LiteralArgument::LiteralArgument(int value)
:value(value){

}

LiteralArgument::~LiteralArgument(){

}

bool LiteralArgument::isResolved(std::map<std::string,SymbolTableEntry*> *symbolTable){
    return true;
}

bool LiteralArgument::isDefined(std::map<std::string,SymbolTableEntry*> *symbolTable){
    return true;
}

short LiteralArgument::getValue(std::map<std::string,SymbolTableEntry*> *symbolTable){
    return value;
}

SymbolTableEntry* LiteralArgument::getSymbol(std::map<std::string,SymbolTableEntry*> *symbolTable){
    return nullptr;
}

std::string LiteralArgument::getName(){
    return "" + value;
}