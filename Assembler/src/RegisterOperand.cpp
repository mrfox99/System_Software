#include "../inc/RegisterOperand.hpp"
#include "../inc/RegisterArgument.hpp"

RegisterOperand::RegisterOperand(RegisterArgument* registerArgument)
:registerArgument(registerArgument){
}

RegisterOperand::~RegisterOperand(){
    delete registerArgument;
}

std::string RegisterOperand::getType(){
    return "r";
}

std::vector<OperandArgument*> RegisterOperand::getArguments(){
    return std::vector<OperandArgument*>{registerArgument};
}

RegisterArgument* RegisterOperand::getRegisterArgument(){
    return registerArgument;
}
