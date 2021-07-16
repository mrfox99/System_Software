#include <stdio.h>
#include <iostream>
#include <utility>
#include <fstream>

#include "../inc/Assembler.hpp"
#include "../inc/Statements.hpp"
#include "../inc/Statement.hpp"
#include "../inc/Section.hpp"
#include "../inc/SymbolTableEntry.hpp"
#include "../inc/RelocationTableEntry.hpp"



extern Statements *ASTRoot;
extern int yyparse();
extern FILE* yyin;

Assembler::Assembler(std::string inputFile, std::string outputFile)
:inputFile(inputFile), outputFile(outputFile){

}

Assembler::~Assembler(){

    delete root;
    for(auto pair: sectionTable){
        delete pair.second;
    }
    for(auto pair: symbolTable){
        delete pair.second;
    }
    for(auto relocationTableEntry: relocationTable){
        delete relocationTableEntry;
    }

}

std::map<std::string, Section*>* Assembler::getSectionTable(){
    return &sectionTable;
}
std::map<std::string, SymbolTableEntry*>* Assembler::getSymbolTable(){
    return &symbolTable;
}
std::vector<RelocationTableEntry*>* Assembler::getRelocationTable(){
    return &relocationTable;
}

Section* Assembler::getActiveSection(){
    return activeSection;
}
void Assembler::setActiveSection(Section* section){
    activeSection = section;
}

int Assembler::assemble(){
    int ret = 0;
    
    if(ret = createAST())
        return ret;

    std::cout << "AST created" << std::endl;

    if(ret = firstPass() < 0)
        return ret;

    std::cout << "First pass done" << std::endl;

    if(ret = secondPass() < 0)
        return ret;

    std::cout << "Second pass done" << std::endl;
        
    if(ret = generateELF())
        return ret;

    std::cout << "ELF generated" << std::endl;

    return 0;
}

int Assembler::createAST(){
    yyin = fopen(inputFile.c_str(), "r");
    int ret = yyparse();
    fclose(yyin);
    root = ret == 0 ? ASTRoot : nullptr;
    ASTRoot = nullptr;
    return ret;
}

int Assembler::firstPass(){

    SymbolTableEntry *symbolTableEntry = new SymbolTableEntry{
                                                        "UNDF",
                                                        0,
                                                        "Global",
                                                        "Relocatable",
                                                        true,
                                                        nullptr
                                                        };
    symbolTable.insert(std::pair<std::string,SymbolTableEntry*>(symbolTableEntry->name, symbolTableEntry));

    Section *section = new Section{
                            symbolTableEntry, 
                            0, 
                            ""
                            };
    sectionTable.insert(std::pair<std::string, Section*>(symbolTableEntry->name, section));

    symbolTableEntry->section = section;

    activeSection = section;

    std::vector<Statement*> statements = root->getStatements();

    for(Statement* statement: statements){
        int ret = statement->updateSymbolTable(this);
        if(ret != 0)
            return ret;
    }
    // for(std::pair<std::string, SymbolTableEntry*> pair: symbolTable){
    //     std::cout << "Name: " << pair.second->name << std::endl;
    //     std::cout << "Value: " << pair.second->value << std::endl;
    //     std::cout << "Section: " << ( (pair.second->section!=nullptr) ? pair.second->section->symbol->name : "//" ) << std::endl;
    //     std::cout << "Defined: " << pair.second->defined << std::endl;
    //     std::cout << "Scope: " << pair.second->scope << std::endl;
    //     std::cout << "Type: " << pair.second->type << std::endl;
    //     std::cout << std::endl;
    // }
    for(std::pair<std::string, SymbolTableEntry*> pair: symbolTable){
        if(pair.second->scope == "Global" &&
            !pair.second->defined){
            std::cout<<"Symbol is global but not defined"<< std::endl;
            return -1;
        }
    }
    return 0;
}
int Assembler::secondPass(){
    for(std::pair<std::string,Section*> pair: sectionTable){
        pair.second->counter = 0;
    }

    activeSection = sectionTable.find("UNDF")->second;

    std::vector<Statement*> statements = root->getStatements();

    for(Statement* statement: statements){
        int ret = statement->generateMachineCode(this);
        if(ret != 0)
            return ret;
    }
    // for(std::pair<std::string, Section*> pair: sectionTable){
    //     std::cout << pair.second->symbol->name << ":" << std::endl;
    //     std::cout << pair.second->machineCode << std::endl;
    // }
    return 0;
}
int Assembler::generateELF(){
    std::ofstream elfFile(outputFile);
    unsigned int symbolCount = 0;
    for(std::pair<std::string, SymbolTableEntry*> pair: symbolTable){
        if(pair.second->scope == "Global" ||
            (pair.second->scope == "Local" && 
            pair.second->type == "Relocatable")){
            symbolCount++;
        }
    }
    elfFile << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;

    elfFile << "---------------------------------" << std::endl;
    elfFile << "NUMBER_OF_SYMBOLS: " << symbolCount << std::endl;
    elfFile << "NUMBER_OF_SECTIONS: " << sectionTable.size() << std::endl;
    elfFile << "NUMBER_OF_RELOCATIONS: " << relocationTable.size() << std::endl;
    elfFile << "---------------------------------" << std::endl;

    elfFile << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    
    elfFile << "---------------------------------" << std::endl;
    for(std::pair<std::string, SymbolTableEntry*> pair: symbolTable){
        if(pair.second->scope == "Global" ||
            (pair.second->scope == "Local" && 
            pair.second->type == "Relocatable")){
            elfFile << "SYMBOL_NAME: " << pair.second->name << std::endl;
            elfFile << "SYMBOL_VALUE: " << pair.second->value << std::endl;
            elfFile << "SYMBOL_SCOPE: " << pair.second->scope << std::endl;
            elfFile << "SYMBOL_TYPE: " << pair.second->type << std::endl;
            elfFile << "SYMBOL_DEFINED: " << pair.second->defined << std::endl;
            elfFile << "SYMBOL_SECTION_NAME: " << ((pair.second->section != nullptr) ? pair.second->section->symbol->name : "//" )<< std::endl;
            elfFile << "---------------------------------" << std::endl;
        }
    }

    elfFile << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;

    elfFile << "---------------------------------" << std::endl;
    for(std::pair<std::string, Section*> pair: sectionTable){
        elfFile << "SECTION_NAME: " << pair.second->symbol->name << std::endl;;
        elfFile << "SECTION_DATA: " << (pair.second->machineCode.empty()? "//" : pair.second->machineCode) << std::endl;
        elfFile << "---------------------------------" << std::endl;
    }
    elfFile << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;

    elfFile << "---------------------------------" << std::endl;
    for(RelocationTableEntry *relocationTableEntry: relocationTable){
        elfFile << "RELOCATION_SECTION_NAME: " << relocationTableEntry->section->symbol->name << std::endl;;
        elfFile << "RELOCATION_OFFSET: " << relocationTableEntry->offset << std::endl;;
        elfFile << "RELOCATION_ADDEND: " << relocationTableEntry->addend << std::endl;;
        elfFile << "RELOCATION_TYPE: " << relocationTableEntry->type << std::endl;;
        elfFile << "RELOCATION_SYMBOL_NAME: " << relocationTableEntry->symbol->name << std::endl;
        elfFile << "---------------------------------" << std::endl;
    }

    elfFile << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;

    return 0;
}