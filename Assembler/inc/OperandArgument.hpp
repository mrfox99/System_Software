#ifndef _OperandArgument_HPP_
#define _OperandArgument_HPP_

#include <map>
#include <string>

struct SymbolTableEntry;

class OperandArgument{

protected:

public:
    OperandArgument();
    virtual ~OperandArgument() = 0;
    virtual bool isResolved(std::map<std::string,SymbolTableEntry*> *symbolTable) = 0;
    virtual bool isDefined(std::map<std::string,SymbolTableEntry*> *symbolTable) = 0;
    virtual short getValue(std::map<std::string,SymbolTableEntry*> *symbolTable) = 0;
    virtual SymbolTableEntry* getSymbol(std::map<std::string,SymbolTableEntry*> *symbolTable) = 0;
    virtual std::string getName() = 0;
};

#endif
