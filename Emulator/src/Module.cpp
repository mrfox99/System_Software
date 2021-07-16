#include "../inc/Module.hpp"

Module::Module(){
}

Module::~Module(){
}

void Module::setCPU(CPU *cpu){
    this->cpu = cpu;
}
#include <iostream>
void Module::setInterruptRequestEntry(
    InterruptRequestEntry interruptRequestEntry
    ){
    this->interruptRequestEntry = interruptRequestEntry;
}
