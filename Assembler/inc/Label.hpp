#ifndef _Label_HPP_
#define _Label_HPP_

#include <map>
#include <vector>
#include <string>

class Assembler;

struct Section;
struct SymbolTableEntry;
struct RelocationTableEntry;

class Label{

protected:
    std::string name;
public:
    Label(std::string name);
    ~Label();

    virtual unsigned int getSize();
    virtual int updateSymbolTable(Assembler *assembler);
    virtual int generateMachineCode(Assembler *assembler);
};

#endif
