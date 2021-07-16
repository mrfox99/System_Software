#include <iostream>
#include <fstream>
#include <regex>

#include "../inc/Emulator.hpp"
#include "../inc/InterruptRequestEntry.hpp"

Emulator::Emulator()
:memory(0xFF00){
    cpu.addModule(0x0000, 0xFF00, &memory);
    cpu.addModule(0xFF00, 0xFF04, &terminal);
    terminal.setInterruptRequestEntry(
        InterruptRequestEntry::TERMINAL_REQUEST_ENTRY
    );
    cpu.addModule(0xFF10, 0xFF12, &timer);
    timer.setInterruptRequestEntry(
        InterruptRequestEntry::TIMER_REQUEST_ENTRY
    );
}

Emulator::~Emulator(){
}

int Emulator::loadMemory(std::string inputFile){
    std::fstream inFile(inputFile);

    std::smatch match;
    unsigned short address = -1;

    std:: string input;
    while(inFile >> input){
        if(input.substr(input.size() - 1, 1) == ":"){
            address = std::stoi(input.substr(0, input.size() - 1), nullptr, 16);
        }
        else{
            cpu.setByte(address++, std::stoi(input, nullptr, 16));
        }
    }
    return 0;
}

int Emulator::start(){
    cpu.start();
    terminal.start();
    timer.start();
    return 0;
}
int Emulator::wait(){
    cpu.join();
    //std::cout << "CPU DONE" <<std::endl;
    terminal.stop();
    //std::cout << "TERMIANL DONE" <<std::endl;
    timer.stop();
    //std::cout << "TIMER DONE" <<std::endl;
    return 0;
}
int Emulator::stop(){
    cpu.stop();
    terminal.stop();
    timer.stop();
    return 0;
}
