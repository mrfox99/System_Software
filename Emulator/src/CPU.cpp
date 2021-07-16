#include <iostream>

#include "../inc/CPU.hpp"

CPU::CPU(){
}

CPU::~CPU(){
}

int CPU::addModule(unsigned short startAddress, unsigned short endAddress, Module* module){
    for(auto pair: modules){
        if((pair.first.first <= startAddress && startAddress < pair.first.second) && 
            (pair.first.first <= endAddress && endAddress < pair.first.second)){
            return -1;
        }
    }
    modules.insert(std::make_pair(std::make_pair(startAddress, endAddress), module));
    module->setCPU(this);
    return 0;
}

void CPU::run(){

    pc = getByte(0) | (getByte(1) << 8);

    while(!end){
        int status = 0;
        //std::cout << "run" << std::endl;
        status = fetchInstruction();
        //std::cout << "fetch" << std::endl;
        if(status == 0){
            status = decodeInstruction();
        }
        //std::cout << "decode" << std::endl;
        if(status == 0){
            executeInstruction();
        }
        //std::cout << "execute" << std::endl;
        if(status >= 0){
            handleInterupt();
        }
        //std::cout << "inter" << std::endl;
    }
}

void CPU::setByte(unsigned short address, unsigned char value){
    for(auto pair: modules){
        if(pair.first.first <= address && address < pair.first.second){
            pair.second->setByte(address - pair.first.first, value);
            return;
        }
    }
    //fatal error
}
char CPU::getByte(unsigned short address){
    for(auto pair: modules){
        if(pair.first.first <= address && address < pair.first.second){
            return pair.second->getByte(address - pair.first.first);
        }
    }
    //fatal error
    return -1;
}

void CPU::setInterrupt(InterruptRequestEntry ire){
    interruptRequest[ire] = true;
}

int CPU::fetchInstruction(){
    instructionSize = 0;

    instructionByte[instructionSize++] = getByte(pc++);
    //std::cout << "TTTT "<< (short)instructionByte[0] << ":" << (short)OperationCode::CALL << std::endl;
    if(!(
        instructionByte[0] == OperationCode::HALT   ||
        instructionByte[0] == OperationCode::INT    ||
        instructionByte[0] == OperationCode::IRET   ||
        instructionByte[0] == OperationCode::CALL   ||
        instructionByte[0] == OperationCode::RET    ||
        instructionByte[0] == OperationCode::JMP    ||
        instructionByte[0] == OperationCode::ADD    ||
        instructionByte[0] == OperationCode::JEQ    ||
        instructionByte[0] == OperationCode::JNE    ||
        instructionByte[0] == OperationCode::JGT    ||
        instructionByte[0] == OperationCode::XCHG   ||
        instructionByte[0] == OperationCode::ADD    ||
        instructionByte[0] == OperationCode::SUB    ||
        instructionByte[0] == OperationCode::MUL    ||
        instructionByte[0] == OperationCode::DIV    ||
        instructionByte[0] == OperationCode::CMP    ||
        instructionByte[0] == OperationCode::NOT    ||
        instructionByte[0] == OperationCode::AND    ||
        instructionByte[0] == OperationCode::OR     ||
        instructionByte[0] == OperationCode::XOR    ||
        instructionByte[0] == OperationCode::TEST   ||
        instructionByte[0] == OperationCode::SHL    ||
        instructionByte[0] == OperationCode::SHR    ||
        instructionByte[0] == OperationCode::LDR    ||
        instructionByte[0] == OperationCode::STR    )){
        
        interruptRequest[
            InterruptRequestEntry::
            BAD_INSTRUCTION_REQUEST_ENTRY
            ] = true;
        std::cout<<"FAIL1"<<std::endl;
        return 1;
    }

    if(instructionByte[0] == OperationCode::HALT ||
        instructionByte[0] == OperationCode::IRET ||
        instructionByte[0] == OperationCode::RET){
        return 0;
    }

    instructionByte[instructionSize++] = getByte(pc++);
    //std::cout<<"REG:" << (instructionByte[1] >> 4) << "REG:"<<(instructionByte[1] & 0x0F)<<std::endl;
    if(
        (
            (
                instructionByte[0] == OperationCode::XCHG   ||
                instructionByte[0] == OperationCode::ADD    ||
                instructionByte[0] == OperationCode::SUB    ||
                instructionByte[0] == OperationCode::MUL    ||
                instructionByte[0] == OperationCode::DIV    ||
                instructionByte[0] == OperationCode::CMP    ||
                instructionByte[0] == OperationCode::AND    ||
                instructionByte[0] == OperationCode::OR     ||
                instructionByte[0] == OperationCode::XOR    ||
                instructionByte[0] == OperationCode::TEST   ||
                instructionByte[0] == OperationCode::SHL    ||
                instructionByte[0] == OperationCode::SHR
            )   
            &&
            (
                (!(
                    (instructionByte[1] >> 4) == Register::R0   ||
                    (instructionByte[1] >> 4) == Register::R1   ||
                    (instructionByte[1] >> 4) == Register::R2   ||
                    (instructionByte[1] >> 4) == Register::R3   ||
                    (instructionByte[1] >> 4) == Register::R4   ||
                    (instructionByte[1] >> 4) == Register::R5   ||
                    (instructionByte[1] >> 4) == Register::R6   ||
                    (instructionByte[1] >> 4) == Register::R7   ||
                    (instructionByte[1] >> 4) == Register::R8 
                ))||
                (!(
                    (instructionByte[1] & 0x0F) == Register::R0    ||
                    (instructionByte[1] & 0x0F) == Register::R1    ||
                    (instructionByte[1] & 0x0F) == Register::R2    ||
                    (instructionByte[1] & 0x0F) == Register::R3    ||
                    (instructionByte[1] & 0x0F) == Register::R4    ||
                    (instructionByte[1] & 0x0F) == Register::R5    ||
                    (instructionByte[1] & 0x0F) == Register::R6    ||
                    (instructionByte[1] & 0x0F) == Register::R7     ||
                    (instructionByte[1] & 0x0F) == Register::R8   
                ))
            )
        )||
        (
            (
                instructionByte[0] == OperationCode::INT    ||
                instructionByte[0] == OperationCode::NOT    ||
                instructionByte[0] == OperationCode::LDR    ||
                instructionByte[0] == OperationCode::STR
            )   
            &&
            (!(
                (instructionByte[1] >> 4) == Register::R0   ||
                (instructionByte[1] >> 4) == Register::R1   ||
                (instructionByte[1] >> 4) == Register::R2   ||
                (instructionByte[1] >> 4) == Register::R3   ||
                (instructionByte[1] >> 4) == Register::R4   ||
                (instructionByte[1] >> 4) == Register::R5   ||
                (instructionByte[1] >> 4) == Register::R6   ||
                (instructionByte[1] >> 4) == Register::R7   ||
                (instructionByte[1] >> 4) == Register::R8   
            ))
        )
    
    ){

        interruptRequest[
            InterruptRequestEntry::
            BAD_INSTRUCTION_REQUEST_ENTRY
            ] = true;
        std::cout<<"FAIL2"<<std::endl;
        return 1;
    }

    if( instructionByte[0] == OperationCode::INT    ||
        instructionByte[0] == OperationCode::XCHG   ||
        instructionByte[0] == OperationCode::ADD    ||
        instructionByte[0] == OperationCode::SUB    ||
        instructionByte[0] == OperationCode::MUL    ||
        instructionByte[0] == OperationCode::DIV    ||
        instructionByte[0] == OperationCode::CMP    ||
        instructionByte[0] == OperationCode::NOT    ||
        instructionByte[0] == OperationCode::AND    ||
        instructionByte[0] == OperationCode::OR     ||
        instructionByte[0] == OperationCode::XOR    ||
        instructionByte[0] == OperationCode::TEST   ||
        instructionByte[0] == OperationCode::SHL    ||
        instructionByte[0] == OperationCode::SHR    ){
        return 0;
    }

    instructionByte[instructionSize++] = getByte(pc++);

    if(
        (!(    
            (instructionByte[2] & 0x0F) == AddressMode::IMMEDIATE                 ||
            (instructionByte[2] & 0x0F) == AddressMode::REGISTER_DIRECT           ||
            (instructionByte[2] & 0x0F) == AddressMode::REGISTER_DIRECT_OFFSET    ||
            (instructionByte[2] & 0x0F) == AddressMode::REGISTER_INDIRECT         ||
            (instructionByte[2] & 0x0F) == AddressMode::REGISTER_INDIRECT_OFFSET  ||
            (instructionByte[2] & 0x0F) == AddressMode::MEMORY
        ))||
        (!(
            (instructionByte[2] >> 4) == UpdateMode::NONE           ||
            (instructionByte[2] >> 4) == UpdateMode::PRE_DECREMENT  ||
            (instructionByte[2] >> 4) == UpdateMode::PRE_INCREMENT  ||
            (instructionByte[2] >> 4) == UpdateMode::POST_DECREMENT ||
            (instructionByte[2] >> 4) == UpdateMode::POST_INCREMENT 
        ))
    
    ){

        interruptRequest[
            InterruptRequestEntry::
            BAD_INSTRUCTION_REQUEST_ENTRY
            ] = true;
        std::cout<<"FAIL3"<<std::endl;
        return 1;
    }

    if(
        (
            instructionByte[0] == OperationCode::CALL   ||
            instructionByte[0] == OperationCode::JMP    ||
            instructionByte[0] == OperationCode::ADD    ||
            instructionByte[0] == OperationCode::JEQ    ||
            instructionByte[0] == OperationCode::JNE    ||
            instructionByte[0] == OperationCode::JGT    ||
            instructionByte[0] == OperationCode::LDR    ||
            instructionByte[0] == OperationCode::STR
        )&&
        (
            (instructionByte[2] & 0x0F) == AddressMode::REGISTER_INDIRECT ||
            (instructionByte[2] & 0x0F) == AddressMode::REGISTER_DIRECT
        )
    ){
        return 0;
    }

    instructionByte[instructionSize++] = getByte(pc++);
    instructionByte[instructionSize++] = getByte(pc++);
    return 0;
}

int CPU::decodeInstruction(){

    if(instructionSize >= 2){
        getDestinationOperand = 
            [this](){
                return reg[instructionByte[1] >> 4];
            };
        setDestinationOperand = 
            [this](short value){
                reg[instructionByte[1] >> 4] = value;
            };

        getSourceOperand = 
            [this](){
                return reg[instructionByte[1] & 0x0F];
            };
        setSourceOperand = 
            [this](short value){
                reg[instructionByte[1] & 0x0F] = value;
            };
    }


    preOperation = [](){};
    postOperation = [](){};
    if(instructionSize >= 3){
        switch (instructionByte[2] >> 4){
            case UpdateMode::PRE_DECREMENT :{
                preOperation =
                    [this](){
                        reg[instructionByte[1] & 0x0F] -= 2;
                    };
                break;
            }

            case UpdateMode::PRE_INCREMENT :{
                preOperation =
                    [this](){
                        reg[instructionByte[1] & 0x0F] += 2;
                    };
                break;
            }

            case UpdateMode::POST_DECREMENT :{
                postOperation =
                    [this](){
                        reg[instructionByte[1] & 0x0F] -= 2;
                    };
                break;
            }

            case UpdateMode::POST_INCREMENT :{
                postOperation =
                    [this](){
                        reg[instructionByte[1] & 0x0F] += 2;
                    };
                break;
            }
        }

        switch (instructionByte[2] & 0x0F){
            case AddressMode::IMMEDIATE :{
                getSourceOperand = 
                    [this](){
                        return instructionByte[3] << 8 | instructionByte[4];
                    };
                setSourceOperand = 
                    [this](short value){
                        //fatal error
                    };
                break;
            }

            case AddressMode::REGISTER_DIRECT_OFFSET :{
                getSourceOperand = 
                    [this](){
                        return reg[instructionByte[1] & 0x0F] + (instructionByte[3] << 8 | instructionByte[4]);
                    };
                setSourceOperand = 
                    [this](short value){
                        //fatal error
                    };
                break;
            }

            case AddressMode::REGISTER_INDIRECT :{
                getSourceOperand = 
                    [this](){
                        unsigned short address = reg[instructionByte[1] & 0x0F];
                        return (getByte(address + 1) << 8) | getByte(address);
                    };
                setSourceOperand = 
                    [this](short value){
                        unsigned short address = reg[instructionByte[1] & 0x0F];
                        setByte(address, value & 0x00FF);
                        setByte(address + 1, value >> 8);
                    };
                break;
            }

            case AddressMode::REGISTER_INDIRECT_OFFSET :{
                getSourceOperand = 
                    [this](){
                        unsigned short address = reg[instructionByte[1] & 0x0F] + (instructionByte[3] << 8 | instructionByte[4]);
                        return (getByte(address + 1) << 8) | getByte(address);
                    };
                setSourceOperand = 
                    [this](short value){
                        unsigned short address = reg[instructionByte[1] & 0x0F] + (instructionByte[3] << 8 | instructionByte[4]);
                        setByte(address, value & 0x00FF);
                        setByte(address + 1, value >> 8);
                    };
                break;
            }

            case AddressMode::MEMORY :{
                getSourceOperand = 
                    [this](){
                        unsigned short address = instructionByte[3] << 8 | instructionByte[4];
                        return (getByte(address + 1) << 8) | getByte(address);
                    };
                setSourceOperand = 
                    [this](short value){
                        unsigned short address = instructionByte[3] << 8 | instructionByte[4];
                        setByte(address, value & 0x00FF);
                        setByte(address + 1, value >> 8);
                    };
                break;
            }
        }
    }

    switch (instructionByte[0]){

        case OperationCode::HALT :{
            operation = [this](){
                end = true;
            };
            break;
        }

        case OperationCode::INT :{
            operation = [this](){
                setByte(sp--, psw >> 8);
                setByte(sp--, psw | 0x00FF);
                short tmp = getDestinationOperand() % 8;
                pc = getByte(tmp * 2);
                pc &= 0x00FF;
                pc |= getByte(tmp * 2 +1) << 8;
            };
            break;
        }

        case OperationCode::IRET :{
            operation = [this](){
                pc = getByte(sp++);
                pc |= getByte(sp++) << 8;
                psw = getByte(sp++);
                psw |= getByte(sp++) << 8;
                
            };
            break;
        }

        case OperationCode::CALL :{
            operation = [this](){
                setByte(sp--, pc >> 8);
                setByte(sp--, pc | 0x00FF);
                pc = getSourceOperand();
            };
            break;
        }

        case OperationCode::RET :{
            operation = [this](){
                pc = getByte(sp++) << 8;
                pc |= getByte(sp++) & 0x00FF;
            };
            break;
        }

        case OperationCode::JMP :{
            operation = [this](){
                pc = getSourceOperand();
            };
            break;
        }

        case OperationCode::JEQ :{
            operation = [this](){
                if(psw & Flags::ZERO_FLAG){
                    pc = getSourceOperand();
                }
            };
            break;
        }

        case OperationCode::JNE :{
            operation = [this](){
                if(!(psw & Flags::ZERO_FLAG)){
                    pc = getSourceOperand();
                }
            };
            break;
        }
        //!(sf^of)&!zf
        case OperationCode::JGT :{
            operation = [this](){
                if(!((psw & Flags::NEGATIVE_FLAG) && (psw & Flags::OVERFLOW_FLAG)) &&
                    !(psw & Flags::ZERO_FLAG)){
                    pc = getSourceOperand();
                }
            };
            break;
        }

        case OperationCode::XCHG :{
            operation = [this](){
                short tmp = getDestinationOperand();
                setDestinationOperand(getSourceOperand());
                setSourceOperand(tmp);
            };
            break;
        }

        case OperationCode::ADD :{
            operation = [this](){
                setDestinationOperand(getDestinationOperand() + getSourceOperand());
            };
            break;
        }

        case OperationCode::SUB :{
            operation = [this](){
                setDestinationOperand(getDestinationOperand() - getSourceOperand());
            };
            break;
        }

        case OperationCode::MUL :{
            operation = [this](){
                setDestinationOperand(getDestinationOperand() * getSourceOperand());
            };
            break;
        }

        case OperationCode::DIV :{
            operation = [this](){
                setDestinationOperand(getDestinationOperand() / getSourceOperand());
            };
            break;
        }

        case OperationCode::CMP :{
            operation = [this](){
                short operandDestination = getDestinationOperand();
                short operandSource = getSourceOperand();
                short tmp =  operandDestination - operandSource;
                if(tmp == 0){
                    psw |= Flags::ZERO_FLAG;
                }
                else{
                    psw &= ~Flags::ZERO_FLAG;
                }

                if((operandDestination > 0 && operandSource < 0 && tmp < 0) ||
                    (operandDestination < 0 && operandSource > 0 && tmp > 0)){
                    psw |= Flags::OVERFLOW_FLAG;
                }
                else{
                    psw &= ~Flags::OVERFLOW_FLAG;
                }
                
                if(((int)operandDestination - (int)operandSource) & 0x10000){
                    psw |= Flags::CARRY_FLAG;
                }
                else{
                    psw &= ~Flags::CARRY_FLAG;
                }

                if(tmp < 0){
                    psw |= Flags::NEGATIVE_FLAG;
                }
                else{
                    psw &= ~Flags::NEGATIVE_FLAG;
                }
            };
            break;
        }

        case OperationCode::NOT :{
            
            operation = [this](){
                setDestinationOperand(~getDestinationOperand());
            };
            break;
        }

        case OperationCode::AND :{
            operation = [this](){
                setDestinationOperand(getDestinationOperand() & getSourceOperand());
            };
            break;
        }

        case OperationCode::OR :{
            operation = [this](){
                setDestinationOperand(getDestinationOperand() | getSourceOperand());
            };
            break;
        }

        case OperationCode::XOR :{
            operation = [this](){
                setDestinationOperand(getDestinationOperand() ^ getSourceOperand());
            };
            break;
        }

        case OperationCode::TEST :{
            operation = [this](){
                short tmp = getDestinationOperand() & getSourceOperand();
                if(tmp == 0){
                    psw |= Flags::ZERO_FLAG;
                }
                else{
                    psw &= ~Flags::ZERO_FLAG;
                }
                if(tmp < 0){
                    psw |= Flags::NEGATIVE_FLAG;
                }
                else{
                    psw &= ~Flags::NEGATIVE_FLAG;
                }
            };
            break;
        }

        case OperationCode::SHL :{
            operation = [this](){
                short operandDestination = getDestinationOperand();
                short result = operandDestination << getSourceOperand();
                setDestinationOperand(result);

                if(result == 0){
                    psw |= Flags::ZERO_FLAG;
                }
                else{
                    psw &= ~Flags::ZERO_FLAG;
                }

                if(operandDestination & 0x8000){
                    psw |= Flags::CARRY_FLAG;
                }
                else{
                    psw &= ~Flags::CARRY_FLAG;
                }

                if(result < 0){
                    psw |= Flags::NEGATIVE_FLAG;
                }
                else{
                    psw &= ~Flags::NEGATIVE_FLAG;
                }
            };
            break;
        }

        case OperationCode::SHR :{
            operation = [this](){
                short operandDestination = getDestinationOperand();
                short result = operandDestination >> getSourceOperand();
                setDestinationOperand(result);

                if(result == 0){
                    psw |= Flags::ZERO_FLAG;
                }
                else{
                    psw &= ~Flags::ZERO_FLAG;
                }

                if(operandDestination & 0x0001){
                    psw |= Flags::CARRY_FLAG;
                }
                else{
                    psw &= ~Flags::CARRY_FLAG;
                }

                if(result < 0){
                    psw |= Flags::NEGATIVE_FLAG;
                }
                else{
                    psw &= ~Flags::NEGATIVE_FLAG;
                }
            };
            break;
        }

        case OperationCode::LDR :{
            operation = [this](){
                setDestinationOperand(getSourceOperand());
            };
            break;
        }

        case OperationCode::STR :{
            operation = [this](){
                setSourceOperand(getDestinationOperand());
            };
            break;
        }
    }
    return 0;
}

int CPU::executeInstruction(){

    preOperation();
    operation();
    postOperation();
    return 0;
}

int CPU::handleInterupt(){
    if(interruptRequest[RESET_PROCESSOR_REQUEST_ENTRY]){
        interruptRequest[RESET_PROCESSOR_REQUEST_ENTRY] = false;
        setByte(--sp, (psw >> 8) & 0x00FF);
        setByte(--sp, psw & 0x00FF);
        setByte(--sp, (pc >> 8) & 0x00FF);
        setByte(--sp, pc & 0x00FF);

        psw &= 0x7FFF;
        pc = getByte(RESET_PROCESSOR_REQUEST_ENTRY * 2);
        pc &= 0x00FF;
        pc |= getByte(RESET_PROCESSOR_REQUEST_ENTRY *2 + 1) << 8;
    }
    else if(interruptRequest[BAD_INSTRUCTION_REQUEST_ENTRY]){
        interruptRequest[BAD_INSTRUCTION_REQUEST_ENTRY] = false;
        setByte(--sp, (psw >> 8) & 0x00FF);
        setByte(--sp, psw & 0x00FF);
        setByte(--sp, (pc >> 8) & 0x00FF);
        setByte(--sp, pc & 0x00FF);

        psw &= 0x7FFF;
        pc = getByte(BAD_INSTRUCTION_REQUEST_ENTRY * 2);
        pc &= 0x00FF;
        pc |= getByte(BAD_INSTRUCTION_REQUEST_ENTRY *2 + 1) << 8;
    }
    else if(interruptRequest[TIMER_REQUEST_ENTRY]
        && (psw & Flags::INTERRUPT_FLAG) && (psw & Flags::TIMER_INRERRUPT_FLAG)){
        interruptRequest[TIMER_REQUEST_ENTRY] = false;
        setByte(--sp, (psw >> 8) & 0x00FF);
        setByte(--sp, psw & 0x00FF);
        setByte(--sp, (pc >> 8) & 0x00FF);
        setByte(--sp, pc & 0x00FF);

        psw &= 0x7FFF;
        pc = getByte(TIMER_REQUEST_ENTRY * 2);
        pc &= 0x00FF;
        pc |= getByte(TIMER_REQUEST_ENTRY *2 + 1) << 8;
    }
    else if(interruptRequest[TERMINAL_REQUEST_ENTRY]
        && (psw & Flags::INTERRUPT_FLAG) && (psw & Flags::TERMINAL_INRERRUPT_FLAG)){
        interruptRequest[TERMINAL_REQUEST_ENTRY] = false;
        setByte(--sp, (psw >> 8) & 0x00FF);
        setByte(--sp, psw & 0x00FF);
        setByte(--sp, (pc >> 8) & 0x00FF);
        setByte(--sp, pc & 0x00FF);

        psw &= 0x7FFF;
        pc = getByte(TERMINAL_REQUEST_ENTRY * 2);
        pc &= 0x00FF;
        pc |= getByte(TERMINAL_REQUEST_ENTRY *2 + 1) << 8;
    }


    // for(int i = 0; i < UNDF_REQUEST_ENTRY; i++){
    //     if(interruptRequest[i]){
    //         //std:: cout << "INTERPUT ENTRY" << (short)i <<std::endl;
    //         interruptRequest[i] = false;
    //         setByte(--sp, (psw >> 8) & 0x00FF);
    //         setByte(--sp, psw & 0x00FF);
    //         setByte(--sp, (pc >> 8) & 0x00FF);
    //         setByte(--sp, pc & 0x00FF);

    //         psw &= 0x7FFF;
    //         pc = getByte(i * 2);
    //         pc &= 0x00FF;
    //         pc |= getByte(i *2 +1) << 8;
    //         return 0;
    //     }
    // }
    return 0;
}
