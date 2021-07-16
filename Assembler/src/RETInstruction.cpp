#include "../inc/RETInstruction.hpp"
#include "../inc/MachineInstruction.hpp"

RETInstruction::RETInstruction(){

}

RETInstruction::~RETInstruction(){

}

MachineInstruction::OperationCode RETInstruction::getOperationCode(){
    return MachineInstruction::OperationCode::RET;
}