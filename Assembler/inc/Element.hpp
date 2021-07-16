#ifndef _Element_HPP_
#define _Element_HPP_

#include <string>
#include <vector>
#include <map>

class Assembler;

struct Section;
struct SymbolTableEntry;
struct RelocationTableEntry;


class Element{
    
public:
    Element();
    virtual ~Element() = 0;
    
    virtual unsigned int getSize() = 0;
    virtual int updateSymbolTable(Assembler *assembler) = 0;
    virtual int generateMachineCode(Assembler *assembler) = 0;
};

#endif
