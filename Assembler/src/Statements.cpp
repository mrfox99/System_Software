#include "../inc/Statements.hpp"
#include "../inc/Statement.hpp"

Statements::Statements(){

}
Statements::~Statements(){
    for(auto statement: statements){
        delete statement;
    }
}

void Statements::addStatement(Statement *statement){
    statements.push_back(statement);
}

std::vector<Statement*> Statements::getStatements(){
    return statements;
}
