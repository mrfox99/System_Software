#ifndef _ASEMBLER_HPP_
#define _ASEMBLER_HPP_

#include <string>
#include <vector>
#include <map>

struct Section;
struct SymbolTableEntry;
struct RelocationTableEntry;
struct Statements;

class Assembler{

protected:
    std::string inputFile;
    std::string outputFile;
    Statements* root;
    std::map<std::string, Section*> sectionTable;
    std::map<std::string, SymbolTableEntry*> symbolTable;
    std::vector<RelocationTableEntry*> relocationTable;
    Section* activeSection;

public:
    Assembler(std::string inputFile, std::string outputFile);
    ~Assembler();
    
    std::map<std::string, Section*>* getSectionTable();
    std::map<std::string, SymbolTableEntry*>* getSymbolTable();
    std::vector<RelocationTableEntry*>* getRelocationTable();

    Section* getActiveSection();
    void setActiveSection(Section* section);

    int assemble();

protected:
    int createAST();
    int firstPass();
    int secondPass();
    int generateELF();
};

#endif
