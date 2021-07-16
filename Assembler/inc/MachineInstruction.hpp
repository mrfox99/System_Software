#ifndef _MachineInstruction_HPP_
#define _MachineInstruction_HPP_

#include <string>

class MachineInstruction{
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
        NONE = 0b0000,
        PRE_DECREMENT = 0b0001,
        PRE_INCREMENT = 0b0010,
        POST_DECREMENT = 0b0011,
        POST_INCREMENT = 0b0100
    };

protected:
    OperationCode op = HALT;
    Register rd = RUNDF;
    Register rs = RUNDF;
    UpdateMode um = NONE;
    AddressMode am = REGISTER_DIRECT;
    unsigned short payload = 0;
    unsigned char size = 0;
    
public:
    MachineInstruction();
    ~MachineInstruction();
    MachineInstruction& setOperationCode(OperationCode op);
    MachineInstruction& setDesitnationRegister(Register rd);
    MachineInstruction& setSourceRegister(Register rs);
    MachineInstruction& setPayload(unsigned short payload);
    MachineInstruction& setAddressMode(AddressMode am);
    MachineInstruction& setUpdateMode(UpdateMode um);
    std::string getInstruction();
};


#endif
