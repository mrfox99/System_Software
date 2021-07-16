#include "../inc/EndDirective.hpp"

EndDirective::EndDirective(){

}

EndDirective::~EndDirective(){

}

unsigned int EndDirective::getSize(){
    return 0;
}

int EndDirective::updateSymbolTable(Assembler *assembler){
    
    return 1;
}

int EndDirective::generateMachineCode(Assembler *assembler){
    return 1;
}