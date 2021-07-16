#ifndef _Linker_hpp
#define _Linker_hpp

#include <string>
#include <vector>
#include <map>
#include <list>

struct Symbol;
struct Section;
struct Relocation;
struct Part;

class Linker{

public:
    struct AddressMap{
        std::string section;
        unsigned int address;
    };

protected:
    std::vector<std::string> inputFiles;
    std::string outputFile;
    std::map<unsigned short, std::string> addressMap;
    std::string mode;

    std::map<std::string, Symbol*> symbols;
    std::map<std::string, Section*> sections;
    std::list<Relocation*> relocations;

public:
    Linker(
        std::vector<std::string> inputFiles,
        std::string outputFile,
        std::map<unsigned short, std::string> addressMap,
        std::string mode
        );
    ~Linker();

    int link();

protected:
    int loadFiles();
    int merge();
    int generateHex();
    int generateLinkable();

    static std::string generateHexFromBinary(std::string binary);
};

#endif
