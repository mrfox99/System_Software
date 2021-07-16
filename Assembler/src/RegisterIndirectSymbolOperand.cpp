#include "../inc/RegisterIndirectSymbolOperand.hpp"
#include "../inc/RegisterArgument.hpp"
#include "../inc/SymbolArgument.hpp"

RegisterIndirectSymbolOperand::RegisterIndirectSymbolOperand(
    RegisterArgument *registerArgument, 
    SymbolArgument *symbolArgument)
:registerArgument(registerArgument), symbolArgument(symbolArgument){
}

RegisterIndirectSymbolOperand::~RegisterIndirectSymbolOperand(){
    delete registerArgument;
    delete symbolArgument;
}

std::string RegisterIndirectSymbolOperand::getType(){
    return "ris";
}

std::vector<OperandArgument*> RegisterIndirectSymbolOperand::getArguments(){
    return std::vector<OperandArgument*>{registerArgument, symbolArgument};
}

RegisterArgument* RegisterIndirectSymbolOperand::getRegisterArgument(){
    return registerArgument;
}

SymbolArgument* RegisterIndirectSymbolOperand::getSymbolArgument(){
    return symbolArgument;
}
