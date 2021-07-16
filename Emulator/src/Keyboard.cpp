#include <iostream>

#include "../inc/Keyboard.hpp"
#include "../inc/Terminal.hpp"

Keyboard::Keyboard(Terminal *terminal)
:terminal(terminal){
}

Keyboard::~Keyboard(){
}

void Keyboard::setLowByte(char value){
    mutex.lock();
    this->value &= 0xFF00;
    this->value |= value;
    mutex.unlock();
}

void Keyboard::setHighByte(char value){
    mutex.lock();
    this->value &= 0x00FF;
    this->value |= value << 8;
    mutex.unlock();
}

char Keyboard::getLowByte(){
    mutex.lock();
    char ret = value & 0x00FF;
    mutex.unlock();
    return ret;
}

char Keyboard::getHighByte(){
    mutex.lock();
    char ret = (value >> 8) & 0x00FF;
    mutex.unlock();
    return ret;
}

void Keyboard::run(){
    while(!end){
        char tmp;
        std::cin >> tmp;
        mutex.lock();
        value = 0x00FF & tmp;
        mutex.unlock();
        terminal->generateInterrupt();
    }
}