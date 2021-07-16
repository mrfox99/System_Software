#include <string>

struct Section;
struct SymbolTableEntry; 

struct RelocationTableEntry{
    Section *section;
    unsigned int offset;
    int addend;
    std::string type;
    SymbolTableEntry* symbol;

};
