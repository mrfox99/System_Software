#ifndef _Section_HPP_
#define _Section_HPP_

#include <string>

struct SymbolTableEntry;

struct Section{
    SymbolTableEntry *symbol;
    unsigned int counter;
    std::string machineCode;
    
};

#endif
