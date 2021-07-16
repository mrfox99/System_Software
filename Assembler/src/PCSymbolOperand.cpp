#include "../inc/PCSymbolOperand.hpp"
#include "../inc/SymbolArgument.hpp"

PCSymbolOperand::PCSymbolOperand(SymbolArgument *symbolArgument)
:symbolArgument(symbolArgument){
}

PCSymbolOperand::~PCSymbolOperand(){
    delete symbolArgument;
}

std::string PCSymbolOperand::getType(){
    return "pcs";
}

std::vector<OperandArgument*> PCSymbolOperand::getArguments(){
    return std::vector<OperandArgument*>{symbolArgument};
}

SymbolArgument* PCSymbolOperand::getSymbolArgument(){
    return symbolArgument;
}