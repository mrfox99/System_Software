#include <iostream>
#include <string>
#include <vector>
#include <termios.h>

#include "../inc/Emulator.hpp"

int main(int argc, char *argv[]){
    struct termios t;
    tcgetattr(fileno(stdin), &t);
    t.c_lflag &= ~ICANON;
    t.c_lflag &= ~ECHO; 
    tcsetattr(fileno(stdin), TCSANOW, &t);
    
    std::vector<std::string> arguments(argv + 1, argv + argc);
    std::string inputFile;

    for(auto it = arguments.begin(); it < arguments.end(); it++){
        if(inputFile.empty()){
                inputFile = *it;
        }
        else{
            return -1;
        }
    }
    if(inputFile.empty()){
        return -1;
    }

    Emulator e;
    //std::cout << "emu created<" << (short)e.terminal.interruptRequestEntry << std::endl;
    e.loadMemory(inputFile);
    //std::cout << "emu createdt" << (short)e.terminal.interruptRequestEntry << std::endl;
    //std::cout << "emu created" << std::endl;
    e.start();
    //std::cout << "emu start" << std::endl;
    //std::cout << "emu createdt" << (short)e.terminal.interruptRequestEntry << std::endl;
    e.wait();
    //std::cout << "emu end" << std::endl;
    //std::cout << e.cpu.reg[0] << std::endl;
    //std::cout << e.cpu.reg[1] << std::endl;
    //std::cout << "emu end" << std::endl;

    tcgetattr(fileno(stdin), &t);
    t.c_lflag |= ICANON;
    t.c_lflag |= ECHO; 
    tcsetattr(fileno(stdin), TCSANOW, &t);
    std::cout << std::endl;
}