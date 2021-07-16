#ifndef _Keyboard_hpp
#define _Keyboard_hpp

#include <mutex>

#include "Thread.hpp"

class Terminal;

class Keyboard: public Thread{

protected:
    Terminal *terminal;

    bool end = false;
    std::mutex mutex;
    short value;

public:
    Keyboard(Terminal *terminal);
    virtual ~Keyboard();

    void setLowByte(char value);
    void setHighByte(char value);
    char getLowByte();
    char getHighByte();

protected:
    virtual void run();
    
};

#endif
