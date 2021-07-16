#ifndef _Statement_HPP_
#define _Statement_HPP_

#include <map>

class Assembler;
class Label;
class Element;

struct Section;
struct SymbolTableEntry;
struct RelocationTableEntry;

class Statement{
protected:
    Label* label = nullptr;
    Element* element = nullptr;
public:
    Statement(Label* label, Element* element);
    Statement(Label* label);
    Statement(Element* element);
    virtual ~Statement();
    
    Label* getLabel();
    Element* getElement();
    int updateSymbolTable(Assembler *assembler);
    int generateMachineCode(Assembler *assembler);
};

#endif
