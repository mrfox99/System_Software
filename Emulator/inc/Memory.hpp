#ifndef _Memory_hpp
#define _Memory_hpp

#include <vector>

#include "Module.hpp"

class Memory: public Module{

protected:
    unsigned int size;
    std::vector<unsigned char> memory;

protected:
    unsigned char& get(unsigned short address);

public:
    Memory(unsigned int size);
    ~Memory();
    virtual void setByte(unsigned short address, unsigned char value);
    virtual unsigned char getByte(unsigned short address);

};

#endif
