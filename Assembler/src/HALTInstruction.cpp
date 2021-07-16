#include "../inc/HALTInstruction.hpp"
#include "../inc/MachineInstruction.hpp"

HALTInstruction::HALTInstruction(){

}

HALTInstruction::~HALTInstruction(){

}

MachineInstruction::OperationCode HALTInstruction::getOperationCode(){
    return MachineInstruction::OperationCode::HALT;
}