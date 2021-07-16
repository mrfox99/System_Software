#include <iostream>

#include "../inc/Display.hpp"

Display::Display()
:lock(mutexWait){
}

Display::~Display(){
}

void Display::setLowByte(char value){
    mutex.lock();
    
    this->value &= 0xFF00;
    this->value |= value;

    lowByteCondition = true;
    lowByteSet = true;
    lowByte.notify_one();

    mutex.unlock();
}
void Display::setHighByte(char value){
    mutex.lock();

    this->value &= 0x00FF;
    this->value |= value << 8;

    highByteCondition = true;
    highByteSet = true;
    highByte.notify_one();

    mutex.unlock();
}
char Display::getLowByte(){
    mutex.lock();
    char ret = value & 0x00FF;
    mutex.unlock();
    return ret;
}
char Display::getHighByte(){
    mutex.lock();
    char ret = (value >> 8) & 0x00FF;
    mutex.unlock();
    return ret;
}

void Display::run(){
    do{
        mutex.lock();
        if(!lowByteCondition){
            mutex.unlock();
            lowByte.wait(lock);
        }
        else{
            mutex.unlock();
        }

        mutex.lock();
        if(!highByteCondition){
            mutex.unlock();
            highByte.wait(lock);
        }
        else{
            mutex.unlock();
        }
        mutex.lock();
        if(lowByteSet && highByteSet){
            std::cout << (char)value << std::flush;
        }
        lowByteCondition = false;
        highByteCondition = false;
        lowByteSet = false;
        highByteSet = false;        
        mutex.unlock();

    }while(!end);
}

int Display::stop(){
    mutex.lock();
    end = true;
    lowByteCondition = true;
    highByteCondition = true;
    lowByte.notify_one();
    highByte.notify_one();
    mutex.unlock();
    return 0;
}