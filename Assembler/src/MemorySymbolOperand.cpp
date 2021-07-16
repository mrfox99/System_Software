#include "../inc/MemorySymbolOperand.hpp"
#include "../inc/SymbolArgument.hpp"

MemorySymbolOperand::MemorySymbolOperand(SymbolArgument *symbolArgument)
:symbolArgument(symbolArgument){
}

MemorySymbolOperand::~MemorySymbolOperand(){
    delete symbolArgument;
}

std::string MemorySymbolOperand::getType(){
    return "ms";
}

std::vector<OperandArgument*> MemorySymbolOperand::getArguments(){
    return std::vector<OperandArgument*>{symbolArgument};
}

SymbolArgument* MemorySymbolOperand::getSymbolArgument(){
    return symbolArgument;
}