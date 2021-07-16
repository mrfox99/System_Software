#include "../inc/MemoryLiteralOperand.hpp"
#include "../inc/LiteralArgument.hpp"

MemoryLiteralOperand::MemoryLiteralOperand(LiteralArgument *literalArgument)
:literalArgument(literalArgument){
}

MemoryLiteralOperand::~MemoryLiteralOperand(){
    delete literalArgument;
}

std::string MemoryLiteralOperand::getType(){
    return "ml";
}

std::vector<OperandArgument*> MemoryLiteralOperand::getArguments(){
    return std::vector<OperandArgument*>{literalArgument};
}

LiteralArgument* MemoryLiteralOperand::getLiteralArgument(){
    return literalArgument;
}