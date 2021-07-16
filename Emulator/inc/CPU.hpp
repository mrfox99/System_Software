#ifndef _CPU_hpp
#define _CPU_hpp

#include <thread>
#include <map>
#include <array>
#include <functional>

#include "Memory.hpp"
#include "Timer.hpp"
#include "Terminal.hpp"
#include "Thread.hpp"
#include "InterruptRequestEntry.hpp"

class Module;

class CPU: public Thread{

public:
    enum OperationCode: unsigned char{
        HALT    = 0b00000000,
        INT     = 0b00010000,
        IRET    = 0b00100000,
        CALL    = 0b00110000,
        RET     = 0b01000000,
        JMP     = 0b01010000,
        JEQ     = 0b01010001,
        JNE     = 0b01010010,
        JGT     = 0b01010011,
        XCHG    = 0b01100000,
        ADD     = 0b01110000,
        SUB     = 0b01110001,
        MUL     = 0b01110010,
        DIV     = 0b01110011,
        CMP     = 0b01110100,
        NOT     = 0b10000000,
        AND     = 0b10000001,
        OR      = 0b10000010,
        XOR     = 0b10000011,
        TEST    = 0b10000100,
        SHL     = 0b10010000,
        SHR     = 0b10010001,
        LDR     = 0b10100000,
        STR     = 0b10110000,
    };

    enum Register: unsigned char{
        R0      = 0b0000,
        R1      = 0b0001,
        R2      = 0b0010,
        R3      = 0b0011,
        R4      = 0b0100,
        R5      = 0b0101,
        R6      = 0b0110,
        SP      = R6    ,
        R7      = 0b0111,
        PC      = R7    ,
        R8      = 0b1000,
        PSW     = R8    ,
        RUNDF   = 0b1111
    };

    static Register getRegister(int r){
        if(0 <= r && r < 9)
            return Register(r);
        return RUNDF;
    }
    enum AddressMode: unsigned char{
        IMMEDIATE = 0b0000,
        REGISTER_DIRECT = 0b0001,
        REGISTER_DIRECT_OFFSET = 0b0101,
        REGISTER_INDIRECT = 0b0010,
        REGISTER_INDIRECT_OFFSET = 0b0011,
        MEMORY = 0b0100
    };
    enum UpdateMode: unsigned char{
        NONE            = 0b0000,
        PRE_DECREMENT   = 0b0001,
        PRE_INCREMENT   = 0b0010,
        POST_DECREMENT  = 0b0011,
        POST_INCREMENT  = 0b0100
    };

    enum Flags: unsigned short{
        INTERRUPT_FLAG              = 0x8000,
        TIMER_INRERRUPT_FLAG        = 0x4000,
        TERMINAL_INRERRUPT_FLAG     = 0x2000,
        NEGATIVE_FLAG               = 0x0008,
        CARRY_FLAG                  = 0x0004,
        OVERFLOW_FLAG               = 0x0002,
        ZERO_FLAG                   = 0x0001
    };

protected:
    short reg[9];
    short &sp = reg[6] = 0xFE00;
    short &pc = reg[7];
    short &psw = reg[8] = 0xE000;
    bool end = false;
    std::array<bool, 4> interruptRequest = {0};

    Memory *memory;
    Timer *timer;
    Terminal *terminal;

    unsigned char instructionByte[5];
    int instructionSize;

    std::function<void()> operation;
    std::function<void()> preOperation;
    std::function<void()> postOperation;
    std::function<short()> getDestinationOperand;
    std::function<void(short)> setDestinationOperand;
    std::function<short()> getSourceOperand;
    std::function<void(short)> setSourceOperand;

    std::map<std::pair<unsigned short, unsigned short>, Module*> modules;

public:
    CPU();
    ~CPU();

    int addModule(unsigned short startAddress, unsigned short endAddress, Module* module);

    void setByte(unsigned short address, unsigned char value);
    char getByte(unsigned short address);

    void setInterrupt(InterruptRequestEntry ire);

protected:
    virtual void run();
    
    int fetchInstruction();
    int decodeInstruction();
    int executeInstruction();
    int handleInterupt();
    
};

#endif
