#include "../inc/IRETInstruction.hpp"
#include "../inc/MachineInstruction.hpp"

IRETInstruction::IRETInstruction(){

}

IRETInstruction::~IRETInstruction(){

}

MachineInstruction::OperationCode IRETInstruction::getOperationCode(){
    return MachineInstruction::OperationCode::IRET;
}