#ifndef _Operand_HPP_
#define _Operand_HPP_

#include <string>
#include <vector>

class OperandArgument;

class Operand{

public:
    Operand();
    virtual ~Operand() = 0 ;
    virtual std::string getType() = 0;
    virtual std::vector<OperandArgument*> getArguments() = 0;
};

#endif
