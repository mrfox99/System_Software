#include "../inc/Memory.hpp"

Memory::Memory(unsigned int size)
:size(size), memory(size, 0){
}

Memory::~Memory(){
}

unsigned char& Memory::get(unsigned short address){
    if(address < size){
        return memory[address];
    }
}

void Memory::setByte(unsigned short address, unsigned char value){
    //std::cout << "WRITE Address:" << address << "Value:" << (int)value<<std::endl;
    get(address) = value;
}

unsigned char Memory::getByte(unsigned short address){
    //std::cout << "READ Address:" << address << "Value:" << (int)get(address)<<std::endl;
    return get(address);
}

