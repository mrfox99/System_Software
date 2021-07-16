#include "../inc/SymbolOperand.hpp"
#include "../inc/SymbolArgument.hpp"

SymbolOperand::SymbolOperand(SymbolArgument *symbolArgument)
:symbolArgument(symbolArgument){
}

SymbolOperand::~SymbolOperand(){
    delete symbolArgument;
}

std::string SymbolOperand::getType(){
    return "s";
}

std::vector<OperandArgument*> SymbolOperand::getArguments(){
    return std::vector<OperandArgument*>{symbolArgument};
}

SymbolArgument* SymbolOperand::getSymbolArgument(){
    return symbolArgument;
}
