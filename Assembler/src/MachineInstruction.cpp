#include <bitset>
#include <string>
#include <algorithm>

#include "../inc/MachineInstruction.hpp"

MachineInstruction::MachineInstruction(){

}

MachineInstruction::~MachineInstruction(){

}

MachineInstruction& MachineInstruction::setOperationCode(OperationCode op){
    this->op = op;
    if(size < 8)
        size = 8;
    return *this;
}
MachineInstruction& MachineInstruction::setDesitnationRegister(Register rd){
    this->rd = rd;
    if(size < 16)
        size = 16;
    return *this;
}
MachineInstruction& MachineInstruction::setSourceRegister(Register rs){
    this->rs = rs;
    if(size < 16)
        size = 16;
    return *this;
}
MachineInstruction& MachineInstruction::setAddressMode(AddressMode am){
    this->am = am;
    if(size < 24)
        size = 24;
    return *this;
}
MachineInstruction& MachineInstruction::setUpdateMode(UpdateMode um){
    this->um = um;
    if(size < 40)
        size = 24;
    return *this;
}
MachineInstruction& MachineInstruction::setPayload(unsigned short payload){
    this->payload = payload;
    if(size < 40)
        size = 40;
    return *this;
}

std::string MachineInstruction::getInstruction(){
    std::bitset<40> instruction;
    if(size >= 8){
        instruction |= std::bitset<40>(op);
    }
    if(size >= 16){
        instruction <<= 8;
        instruction |= (std::bitset<40>(rd) << 4) | std::bitset<40>(rs);
    }
    if(size >= 24){
        instruction <<= 8;
        instruction |= (std::bitset<40>(um) << 4) | std::bitset<40>(am);
    }
    if(size == 40){
        instruction <<= 16;
        instruction |= std::bitset<40>(payload);
    }
    std::string tmp = instruction.to_string();
    return tmp.substr(40 - size, size);
}