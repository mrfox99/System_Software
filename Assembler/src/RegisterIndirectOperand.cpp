#include "../inc/RegisterIndirectOperand.hpp"
#include "../inc/RegisterArgument.hpp"

RegisterIndirectOperand::RegisterIndirectOperand(RegisterArgument* registerArgument)
:registerArgument(registerArgument){
}

RegisterIndirectOperand::~RegisterIndirectOperand(){
    delete registerArgument;
}

std::string RegisterIndirectOperand::getType(){
    return "ri";
}

std::vector<OperandArgument*> RegisterIndirectOperand::getArguments(){
    return std::vector<OperandArgument*>{registerArgument};
}

RegisterArgument* RegisterIndirectOperand::getRegisterArgument(){
    return registerArgument;
}