#include <map>
#include <vector>
#include <string>

struct Section;
struct Symbol;
struct Relocation;

struct Part{
    std::map<std::string, Symbol*> localSymbols;
    std::map<std::string, Section*> sections;
    std::vector<Relocation*> relocations;
};
