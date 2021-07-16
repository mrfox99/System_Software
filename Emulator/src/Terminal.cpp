#include "../inc/Terminal.hpp"
#include "../inc/CPU.hpp"

Terminal::Terminal()
:keyboard(this){
}

Terminal::~Terminal(){
}
#include <iostream>
void Terminal::setByte(unsigned short address, unsigned char value){
    switch (address){
        case 0:{
            display.setLowByte(value);
            return;
        }
        case 1:{
            display.setHighByte(value);
            return;
        }
        case 2:{
            keyboard.setLowByte(value);
            return;
        }
        case 3:{
            keyboard.setHighByte(value);
            return;
        }
        default:{
            //fatal error
            return;
        }
    }
}

unsigned char Terminal::getByte(unsigned short address){
    switch (address){
        case 0:{
            return display.getLowByte();
        }
        case 1:{
            return display.getHighByte();
        }
        case 2:{
            return keyboard.getLowByte();
        }
        case 3:{
            return keyboard.getHighByte();
        }
        default:{
            //fatal error
            return -1;
        }
    }
}

void Terminal::generateInterrupt(){
    cpu->setInterrupt(interruptRequestEntry);
}

int Terminal::start(){
    display.start();
    keyboard.start();
    return 0;
}

int Terminal::stop(){
    display.stop();
    keyboard.stop();
    return 0;
}
