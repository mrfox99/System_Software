#ifndef _LiteralArgument_HPP_
#define _LiteralArgument_HPP_

#include "OperandArgument.hpp"

class LiteralArgument: public OperandArgument{

protected:
    int value;
    
public:
    LiteralArgument(int value);
    ~LiteralArgument();

    virtual bool isResolved(std::map<std::string,SymbolTableEntry*> *symbolTable);
    virtual bool isDefined(std::map<std::string,SymbolTableEntry*> *symbolTable);
    virtual short getValue(std::map<std::string,SymbolTableEntry*> *symbolTable);
    virtual SymbolTableEntry* getSymbol(std::map<std::string,SymbolTableEntry*> *symbolTable);
    virtual std::string getName();
};

#endif
