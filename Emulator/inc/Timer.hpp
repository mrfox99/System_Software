#ifndef _Timer_hpp
#define _Timer_hpp

#include <map>

#include "Module.hpp"
#include "Thread.hpp"

class Timer: public Module, public Thread{

protected:
    bool end = false;
    short value = 1;
    std::map<unsigned short, unsigned long> time = {
        {0, 500},
        {1, 1000},
        {2, 1500},
        {3, 2000},
        {4, 5000},
        {5, 10000},
        {6, 30000},
        {7, 60000},
    };
    
public:
    Timer();
    virtual ~Timer();
    virtual void setByte(unsigned short address, unsigned char value);
    virtual unsigned char getByte(unsigned short address);

protected:
    virtual void run();
};

#endif
