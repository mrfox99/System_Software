#include "../inc/RegisterIndirectLiteralOperand.hpp"
#include "../inc/RegisterArgument.hpp"
#include "../inc/LiteralArgument.hpp"

RegisterIndirectLiteralOperand::RegisterIndirectLiteralOperand(
    RegisterArgument* registerArgument, 
    LiteralArgument *literalArgument)
:registerArgument(registerArgument), literalArgument(literalArgument){
}

RegisterIndirectLiteralOperand::~RegisterIndirectLiteralOperand(){
    delete registerArgument;
    delete literalArgument;
}

std::string RegisterIndirectLiteralOperand::getType(){
    return "ril";
}

std::vector<OperandArgument*> RegisterIndirectLiteralOperand::getArguments(){
    return std::vector<OperandArgument*>{registerArgument, literalArgument};
}

RegisterArgument* RegisterIndirectLiteralOperand::getRegisterArgument(){
    return registerArgument;
}

LiteralArgument* RegisterIndirectLiteralOperand::getLiteralArgument(){
    return literalArgument;
}
