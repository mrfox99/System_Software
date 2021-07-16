#include <vector>
#include <string>
#include <map>

#include "../inc/Statement.hpp"
#include "../inc/Label.hpp"
#include "../inc/Element.hpp"

struct Section;
struct SymbolTableEntry;
struct RelocationTableEntry;

Statement::Statement(Label* label, Element* element)
:label(label), element(element){

}
Statement::Statement(Label* label)
:label(label){

}
Statement::Statement(Element* element)
:element(element){

}

Statement::~Statement(){
    if(label)
        delete label;
    if(element)
        delete element;
}

Label* Statement::getLabel(){
    return label;
}

Element* Statement::getElement(){
    return element;
}

int Statement::updateSymbolTable(Assembler *assembler){

    if(label != nullptr){
        int ret = label->updateSymbolTable(assembler);
        if(ret != 0)
            return ret;
    }

    if(element != nullptr){
        int ret = element->updateSymbolTable(assembler);
        if(ret != 0)
            return ret;
    }

    return 0;
}
int Statement::generateMachineCode(Assembler *assembler){
    if(element != nullptr){
        int ret = element->generateMachineCode(assembler);
        if(ret != 0)
            return ret;
    }
    return 0;
}