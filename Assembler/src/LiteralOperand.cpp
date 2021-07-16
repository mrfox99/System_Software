#include "../inc/LiteralOperand.hpp"
#include "../inc/LiteralArgument.hpp"

LiteralOperand::LiteralOperand(LiteralArgument *literalArgument)
:literalArgument(literalArgument){
}

LiteralOperand::~LiteralOperand(){
    delete literalArgument;
}

std::string LiteralOperand::getType(){
    return "l";
}

std::vector<OperandArgument*> LiteralOperand::getArguments(){
    return std::vector<OperandArgument*>{literalArgument};
}

LiteralArgument* LiteralOperand::getLiteralArgument(){
    return literalArgument;
}
