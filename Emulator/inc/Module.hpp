#ifndef _Module_hpp
#define _Module_hpp

#include "InterruptRequestEntry.hpp"

class CPU;

class Module{

//protected:
public:
    CPU *cpu = nullptr;
    InterruptRequestEntry interruptRequestEntry 
        = InterruptRequestEntry::UNDF_REQUEST_ENTRY;

public:
    Module();
    virtual ~Module();
    void setCPU(CPU *cpu);
    void setInterruptRequestEntry(InterruptRequestEntry interruptRequestEntry);
    virtual void setByte(unsigned short address, unsigned char value) = 0;
    virtual unsigned char getByte(unsigned short address) = 0;
};

#endif
