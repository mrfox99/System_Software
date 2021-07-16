#ifndef _Symbol_HPP_
#define _Symbol_HPP_

#include <string>

#include "OperandArgument.hpp"

class SymbolArgument: public OperandArgument{
protected:
    std::string name;
public:
    SymbolArgument(std::string name);
    virtual ~SymbolArgument();
    virtual bool isResolved(std::map<std::string,SymbolTableEntry*> *symbolTable);
    virtual bool isDefined(std::map<std::string,SymbolTableEntry*> *symbolTable);
    virtual short getValue(std::map<std::string,SymbolTableEntry*> *symbolTable);
    virtual SymbolTableEntry* getSymbol(std::map<std::string,SymbolTableEntry*> *symbolTable);
    virtual std::string getName();
};

#endif
