#ifndef _Emulator_hpp
#define _Emulator_hpp

#include <string>

#include "CPU.hpp"
#include "Memory.hpp"
#include "Terminal.hpp"
#include "Timer.hpp"

class Emulator{

//protected:
public:
    CPU cpu;
    Memory memory;
    Terminal terminal;
    Timer timer;

public:
    Emulator();
    ~Emulator();

    int loadMemory(std::string inputFile);

    int start();
    int wait();
    int stop();
};

#endif
