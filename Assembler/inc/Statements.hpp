#ifndef _Statements_HPP_
#define _Statements_HPP_

#include <vector>

class Statement;

class Statements{

protected:
    std::vector<Statement*> statements;

public:
    Statements();
    virtual ~Statements();
    void addStatement(Statement *statement);
    std::vector<Statement*> getStatements();
};


#endif
