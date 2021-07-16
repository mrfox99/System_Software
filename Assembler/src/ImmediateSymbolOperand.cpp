#include "../inc/ImmediateSymbolOperand.hpp"
#include "../inc/SymbolArgument.hpp"

ImmediateSymbolOperand::ImmediateSymbolOperand(SymbolArgument *symbolArgument)
:symbolArgument(symbolArgument){
}

ImmediateSymbolOperand::~ImmediateSymbolOperand(){
    delete symbolArgument;
}

std::string ImmediateSymbolOperand::getType(){
    return "is";
}

std::vector<OperandArgument*> ImmediateSymbolOperand::getArguments(){
    return std::vector<OperandArgument*>{symbolArgument};
}

SymbolArgument* ImmediateSymbolOperand::getSymbolArgument(){
    return symbolArgument;
}