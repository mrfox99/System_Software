#include <bitset>
#include <iostream>

#include "../inc/WordDirective.hpp"
#include "../inc/Assembler.hpp"
#include "../inc/Section.hpp"
#include "../inc/SymbolTableEntry.hpp"
#include "../inc/RelocationTableEntry.hpp"
#include "../inc/Operand.hpp"
#include "../inc/OperandArgument.hpp"

WordDirective::WordDirective(std::vector<Operand*> operands){
    this->operands = operands;
}

WordDirective::~WordDirective(){
    for(auto operand: operands){
        delete operand;
    }
}

unsigned int WordDirective::getSize(){
    return operands.capacity() * 2;
}

int WordDirective::updateSymbolTable(Assembler *assembler){
    return 0;
}

int WordDirective::generateMachineCode(Assembler *assembler){
    std::string data = "";
    for(Operand *operand : operands){
        
        
        if(operand->getType() == "l"){
            unsigned short tmp = operand->getArguments()[0]->getValue(assembler->getSymbolTable());
            data += std::bitset<16>((tmp << 8) | (tmp >> 8)).to_string();
        }
        else if(operand->getType() == "s"){
            if(!operand->getArguments()[0]->isResolved(assembler->getSymbolTable())){
                std::cout << "Symbol not resolved" << std::endl;
                return -1;
            }

            SymbolTableEntry *symbol = operand->getArguments()[0]->getSymbol(assembler->getSymbolTable());

            if(symbol->type == "Absolute"){
                data +=  std::bitset<16>((symbol->value >> 8) | (symbol->value << 8)).to_string();
            }
            else if(symbol->type == "Relocatable"){
                int addend = 0;
                if(symbol->scope == "Local"){
                    addend = symbol->value;
                    symbol = symbol->section->symbol;
                }
                assembler->getRelocationTable()->push_back(
                    new RelocationTableEntry{
                        assembler->getActiveSection(),
                        assembler->getActiveSection()->counter,
                        addend,
                        "HIPO-16-DATA",
                        symbol
                    }
                );

                data += "0000000000000000";
            }
            else{
                std::cout << "FAIL" << std::endl;
                return -1;
            }

        }
        else{
            std::cout<<"FAIL"<<std::endl;
            return -1;
        }

        
        
    }
    assembler->getActiveSection()->machineCode += data;
    assembler->getActiveSection()->counter += getSize();
    return 0;
}