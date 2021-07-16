#include <string>

struct Section;
struct Symbol;

struct Relocation{
    std::string sectionName;
    unsigned int offset;
    int addend;
    std::string type;
    std::string symbolName;
};
