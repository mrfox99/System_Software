#include <string>

struct Section;

struct SymbolTableEntry{
    // enum Scope{
    //     LOCAL,
    //     GLOBAL,
    //     EXTERN
    // };
    
    // enum Type{
    //     RELOCATABLE,
    //     ABSOLUTE
    // };

    std::string name;
    unsigned short value;
    std::string scope;
    std::string type;
    bool defined;
    Section *section;
};
