#ifndef _Terminal_hpp
#define _Terminal_hpp

#include "Module.hpp"
#include "Display.hpp"
#include "Keyboard.hpp"

class Terminal: public Module{

protected:
    Display display;
    Keyboard keyboard;
    short term_in;
    short term_out;
public:
    Terminal();
    ~Terminal();
    virtual void setByte(unsigned short address, unsigned char value);
    virtual unsigned char getByte(unsigned short address);
    void generateInterrupt();

    int start();
    int stop();
};


#endif
