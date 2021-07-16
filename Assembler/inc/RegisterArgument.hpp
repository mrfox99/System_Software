#include "OperandArgument.hpp"

class RegisterArgument: public OperandArgument{
protected:
    char reg;
public:
    RegisterArgument(char reg);
    virtual ~RegisterArgument();
    virtual bool isResolved(std::map<std::string,SymbolTableEntry*> *symbolTable);
    virtual bool isDefined(std::map<std::string,SymbolTableEntry*> *symbolTable);
    virtual short getValue(std::map<std::string,SymbolTableEntry*> *symbolTable = nullptr);
    virtual SymbolTableEntry* getSymbol(std::map<std::string,SymbolTableEntry*> *symbolTable);
    virtual std::string getName();
};
