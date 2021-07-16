#include "../inc/ImmediateLiteralOperand.hpp"
#include "../inc/LiteralArgument.hpp"

ImmediateLiteralOperand::ImmediateLiteralOperand(LiteralArgument* literalArgument)
:literalArgument(literalArgument){
}

ImmediateLiteralOperand::~ImmediateLiteralOperand(){
    delete literalArgument;
}

std::string ImmediateLiteralOperand::getType(){
    return "il";
}

std::vector<OperandArgument*> ImmediateLiteralOperand::getArguments(){
    return std::vector<OperandArgument*>{literalArgument};
}

LiteralArgument* ImmediateLiteralOperand::getLiteralArgument(){
    return literalArgument;
}
