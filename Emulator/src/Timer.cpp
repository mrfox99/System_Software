#include <chrono>

#include "../inc/Timer.hpp"
#include "../inc/CPU.hpp"

Timer::Timer(){
}

Timer::~Timer(){
}

void Timer::setByte(unsigned short address, unsigned char value){
    switch (address){
        case 0:{
            this->value &= 0xFF00;
            this->value |= value;
            break;
        }
        
        case 1:{
            this->value &= 0x00FF;
            this->value |= value << 8;
            break;
        }
    }
}
unsigned char Timer::getByte(unsigned short address){
    switch (address){
        case 0:{
            return value & 0x00FF;
        }
        
        case 1:{
            return value = 0xFF00;
        }
    }
}

void Timer::run(){
    while(!end){
        unsigned long sleepTime = -1;
        auto it = time.find(value);
        if(it != time.end()){
            sleepTime = it->second;
        }
        
        if(sleepTime != -1){
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
            cpu->setInterrupt(interruptRequestEntry);
        }
    }
}
