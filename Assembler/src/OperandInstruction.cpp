#include "../inc/OperandInstruction.hpp"
#include "../inc/Assembler.hpp"
#include "../inc/Operand.hpp"
#include "../inc/OperandArgument.hpp"
#include "../inc/Section.hpp"
#include "../inc/SymbolTableEntry.hpp"
#include "../inc/RelocationTableEntry.hpp"

#include <iostream>
#include <exception>

OperandInstruction::OperandInstruction(Operand *operand)
:operand(operand){
}

OperandInstruction::~OperandInstruction(){
    delete operand;
}

unsigned int OperandInstruction::getSize(){
    std::string type = this->getType();
    if(type == "#il#")
        return 5;
    else if(type == "#is#")
        return 5;
    else if(type == "#pcs#")
        return 5;
    else if(type == "#ml#")
        return 5;
    else if(type == "#ms#")
        return 5;
    else if(type == "#r#")
        return 3;
    else if(type == "#ri#")
        return 3;
    else if(type == "#ril#")
        return 5;
    else if(type == "#ris#")
        return 5;
    else 
        return -1;
}

MachineInstruction OperandInstruction::getMachineInstruction(Assembler *assembler){
    std::string type = getType();
    MachineInstruction mi;
    mi.setOperationCode(getOperationCode());
    //std::cout << type <<std::endl;
    if(type == "#il#"){
        mi
            .setUpdateMode(MachineInstruction::UpdateMode::NONE)
            .setAddressMode(MachineInstruction::AddressMode::IMMEDIATE)
            .setPayload(operand->getArguments()[0]->getValue(assembler->getSymbolTable()));
    }
    else if(type == "#is#"){
        if(!operand->getArguments()[0]->isResolved(assembler->getSymbolTable())){
                std::cout << "Symbol not resolved" << std::endl;
                throw std::exception();
            }
        short payload = 0;
        SymbolTableEntry *symbol = operand->getArguments()[0]->getSymbol(assembler->getSymbolTable());
        
        if(symbol->type == "Absolute"){
            payload = symbol->value;        
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
                    assembler->getActiveSection()->counter + 3,
                    addend,
                    "HIPO-16-PAYLOAD",
                    symbol
                }
            );
        }
        else{
            throw std::exception();
        }

        mi
            .setUpdateMode(MachineInstruction::UpdateMode::NONE)
            .setAddressMode(MachineInstruction::AddressMode::IMMEDIATE)
            .setPayload(payload);
    }
    else if(type == "#pcs#"){
        if(!operand->getArguments()[0]->isResolved(assembler->getSymbolTable())){
                std::cout << "Symbol not resolved" << std::endl;
                throw std::exception();
            }
        short payload = 0;
        SymbolTableEntry *symbol = operand->getArguments()[0]->getSymbol(assembler->getSymbolTable());
        
        if(symbol->type == "Absolute"){
            payload = symbol->value - ( assembler->getActiveSection()->counter + getSize() );       
        }
        else if(symbol->type == "Relocatable"){

            if(assembler->getActiveSection() == symbol->section){
                payload = symbol->value - ( assembler->getActiveSection()->counter + getSize() );
            }
            else {
                int addend = -2; //(*activeSection)->counter + 3 - (*activeSection)->counter + getSize() 
                if(symbol->scope == "Local"){
                    addend += symbol->value;
                    symbol = symbol->section->symbol;
                }

                assembler->getRelocationTable()->push_back(
                    new RelocationTableEntry{
                        assembler->getActiveSection(),
                        assembler->getActiveSection()->counter + 3,
                        addend, //- (assembler->getActiveSection()->counter + 3 - symbol->value),
                        "HIPO-16PC-PAYLOAD",
                        symbol
                    }
                );
            }
        }
        else{
            throw std::exception();
        }

        mi
            .setUpdateMode(MachineInstruction::UpdateMode::NONE)
            .setSourceRegister(MachineInstruction::Register::PC)
            .setAddressMode(MachineInstruction::AddressMode::REGISTER_INDIRECT_OFFSET)
            .setPayload(payload);
    }
    else if(type == "#ml#"){
        
        mi
            .setUpdateMode(MachineInstruction::UpdateMode::NONE)
            .setAddressMode(MachineInstruction::AddressMode::MEMORY)
            .setPayload(operand->getArguments()[0]->getValue(assembler->getSymbolTable()));
    }
    else if(type == "#ms#"){
        if(!operand->getArguments()[0]->isResolved(assembler->getSymbolTable())){
                std::cout << "Symbol not resolved" << std::endl;
                throw std::exception();
            }
        short payload = 0;
        SymbolTableEntry *symbol = operand->getArguments()[0]->getSymbol(assembler->getSymbolTable());
        
        if(symbol->type == "Absolute"){
            payload = symbol->value;        
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
                    assembler->getActiveSection()->counter + 3,
                    addend,
                    "HIPO-16-PAYLOAD",
                    symbol
                }
            );
        }
        else{
            throw std::exception();
        }

        mi
            .setUpdateMode(MachineInstruction::UpdateMode::NONE)
            .setAddressMode(MachineInstruction::AddressMode::MEMORY)
            .setPayload(payload);
    }
    else if(type == "#r#"){
        mi
            .setSourceRegister(MachineInstruction::getRegister(
                operand->getArguments()[0]->getValue(assembler->getSymbolTable())))
            .setUpdateMode(MachineInstruction::UpdateMode::NONE)
            .setAddressMode(MachineInstruction::AddressMode::REGISTER_DIRECT);
    }
    else if(type == "#ri#"){
        mi
            .setSourceRegister(MachineInstruction::getRegister(
                operand->getArguments()[0]->getValue(assembler->getSymbolTable())))
            .setUpdateMode(MachineInstruction::UpdateMode::NONE)
            .setAddressMode(MachineInstruction::AddressMode::REGISTER_INDIRECT);
    }
    else if(type == "#ril#"){
        mi
            .setSourceRegister(MachineInstruction::getRegister(
                operand->getArguments()[0]->getValue(assembler->getSymbolTable())))
            .setUpdateMode(MachineInstruction::UpdateMode::NONE)
            .setAddressMode(MachineInstruction::AddressMode::REGISTER_INDIRECT_OFFSET)
            .setPayload(operand->getArguments()[1]->getValue(assembler->getSymbolTable()));
    }
    else if(type == "#ris#"){
        if(!operand->getArguments()[1]->isResolved(assembler->getSymbolTable())){
                std::cout << "Symbol not resolved" << std::endl;
                throw std::exception();
            }
        short payload = 0;
        SymbolTableEntry *symbol = operand->getArguments()[1]->getSymbol(assembler->getSymbolTable());
            
        if(symbol->type == "Absolute"){
            payload = symbol->value;        
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
                    assembler->getActiveSection()->counter + 3,
                    addend,
                    "HIPO-16-PAYLOAD",
                    symbol
                }
            );
        }
        else{
            throw std::exception();
        }

        mi
            .setSourceRegister(MachineInstruction::getRegister(
                    operand->getArguments()[0]->getValue(assembler->getSymbolTable())))
            .setUpdateMode(MachineInstruction::UpdateMode::NONE)
            .setAddressMode(MachineInstruction::AddressMode::REGISTER_INDIRECT_OFFSET)
            .setPayload(payload);
    }
    else{
        throw std::exception();
    }

    return mi;
}

int OperandInstruction::generateMachineCode(Assembler *assembler){

    
    // std::string type = getType();
    // MachineInstruction mi;
    // mi.setOperationCode(getOperationCode());

    // if(type == "#il#"){
    //     mi
    //         .setUpdateMode(MachineInstruction::UpdateMode::NONE)
    //         .setAddressMode(MachineInstruction::AddressMode::IMMEDIATE)
    //         .setPayload(operand->getArguments()[0]->getValue(assembler->getSymbolTable()));
    // }
    // else if(type == "#is#"){
    //     if(!operand->getArguments()[0]->isResolved(assembler->getSymbolTable())){
    //             std::cout << "Symbol not resolved" << std::endl;
    //             return -1;
    //         }
    //     short payload = 0;
    //     SymbolTableEntry *symbol = operand->getArguments()[0]->getSymbol(assembler->getSymbolTable());
        
    //     if(symbol->type == "Absolute"){
    //         payload = symbol->value;        
    //     }
    //     else if(symbol->type == "Relocatable"){
        
    //         unsigned int addend = 0;
    //         if(symbol->scope == "Local"){
    //             addend = symbol->value;
    //             symbol = symbol->section->symbol;
    //         }
    //         assembler->getRelocationTable()->push_back(
    //             new RelocationTableEntry{
    //                 assembler->getActiveSection(),
    //                 assembler->getActiveSection()->counter + 3,
    //                 addend,
    //                 "HIPO-16-PAYLOAD",
    //                 symbol
    //             }
    //         );
    //     }
    //     else{
    //         return -1;
    //     }

    //     mi
    //         .setUpdateMode(MachineInstruction::UpdateMode::NONE)
    //         .setAddressMode(MachineInstruction::AddressMode::IMMEDIATE)
    //         .setPayload(payload);
    // }
    // else if(type == "#pcs#"){
    //     if(!operand->getArguments()[0]->isResolved(assembler->getSymbolTable())){
    //             std::cout << "Symbol not resolved" << std::endl;
    //             return -1;
    //         }
    //     short payload = 0;
    //     SymbolTableEntry *symbol = operand->getArguments()[0]->getSymbol(assembler->getSymbolTable());
        
    //     if(symbol->type == "Absolute"){
    //         payload = symbol->value - ( assembler->getActiveSection()->counter + getSize() );       
    //     }
    //     else if(symbol->type == "Relocatable"){

    //         if(assembler->getActiveSection() == symbol->section){
    //             payload = symbol->value - ( assembler->getActiveSection()->counter + getSize() );
    //         }
    //         else {
    //             unsigned int addend = -2; //(*activeSection)->counter + 3 - (*activeSection)->counter + getSize() 
    //             if(symbol->scope == "Local"){
    //                 addend += symbol->value;
    //                 symbol = symbol->section->symbol;
    //             }

    //             assembler->getRelocationTable()->push_back(
    //                 new RelocationTableEntry{
    //                     assembler->getActiveSection(),
    //                     assembler->getActiveSection()->counter + 3,
    //                     addend, //- (assembler->getActiveSection()->counter + 3 - symbol->value),
    //                     "HIPO-16PC-PAYLOAD",
    //                     symbol
    //                 }
    //             );
    //         }
    //     }
    //     else{
    //         return -1;
    //     }

    //     mi
    //         .setUpdateMode(MachineInstruction::UpdateMode::NONE)
    //         .setSourceRegister(MachineInstruction::Register::PC)
    //         .setAddressMode(MachineInstruction::AddressMode::REGISTER_INDIRECT_OFFSET)
    //         .setPayload(payload);
    // }
    // else if(type == "#ml#"){
    //     mi
    //         .setUpdateMode(MachineInstruction::UpdateMode::NONE)
    //         .setAddressMode(MachineInstruction::AddressMode::MEMORY)
    //         .setPayload(operand->getArguments()[0]->getValue(assembler->getSymbolTable()));
    // }
    // else if(type == "#ms#"){
    //     if(!operand->getArguments()[0]->isResolved(assembler->getSymbolTable())){
    //             std::cout << "Symbol not resolved" << std::endl;
    //             return -1;
    //         }
    //     short payload = 0;
    //     SymbolTableEntry *symbol = operand->getArguments()[0]->getSymbol(assembler->getSymbolTable());
        
    //     if(symbol->type == "Absolute"){
    //         payload = symbol->value;        
    //     }
    //     else if(symbol->type == "Relocatable"){
        
    //         unsigned int addend = 0;
    //         if(symbol->scope == "Local"){
    //             addend = symbol->value;
    //             symbol = symbol->section->symbol;
    //         }
    //         assembler->getRelocationTable()->push_back(
    //             new RelocationTableEntry{
    //                 assembler->getActiveSection(),
    //                 assembler->getActiveSection()->counter + 3,
    //                 addend,
    //                 "HIPO-16-PAYLOAD",
    //                 symbol
    //             }
    //         );
    //     }
    //     else{
    //         return -1;
    //     }

    //     mi
    //         .setUpdateMode(MachineInstruction::UpdateMode::NONE)
    //         .setAddressMode(MachineInstruction::AddressMode::MEMORY)
    //         .setPayload(payload);
    // }
    // else if(type == "#r#"){
    //     mi
    //         .setSourceRegister(MachineInstruction::getRegister(
    //             operand->getArguments()[0]->getValue(assembler->getSymbolTable())))
    //         .setUpdateMode(MachineInstruction::UpdateMode::NONE)
    //         .setAddressMode(MachineInstruction::AddressMode::REGISTER_DIRECT);
    // }
    // else if(type == "#ri#"){
    //     mi
    //         .setSourceRegister(MachineInstruction::getRegister(
    //             operand->getArguments()[0]->getValue(assembler->getSymbolTable())))
    //         .setUpdateMode(MachineInstruction::UpdateMode::NONE)
    //         .setAddressMode(MachineInstruction::AddressMode::REGISTER_INDIRECT);
    // }
    // else if(type == "#ril#"){
    //     mi
    //         .setSourceRegister(MachineInstruction::getRegister(
    //             operand->getArguments()[0]->getValue(assembler->getSymbolTable())))
    //         .setUpdateMode(MachineInstruction::UpdateMode::NONE)
    //         .setAddressMode(MachineInstruction::AddressMode::REGISTER_INDIRECT_OFFSET)
    //         .setPayload(operand->getArguments()[1]->getValue(assembler->getSymbolTable()));
    // }
    // else if(type == "#ris#"){
    //     if(!operand->getArguments()[1]->isResolved(assembler->getSymbolTable())){
    //             std::cout << "Symbol not resolved" << std::endl;
    //             return -1;
    //         }
    //     short payload = 0;
    //     SymbolTableEntry *symbol = operand->getArguments()[1]->getSymbol(assembler->getSymbolTable());
            
    //     if(symbol->type == "Absolute"){
    //         payload = symbol->value;        
    //     }
    //     else if(symbol->type == "Relocatable"){
            
    //         unsigned int addend = 0;
    //         if(symbol->scope == "Local"){
    //             addend = symbol->value;
    //             symbol = symbol->section->symbol;
    //         }
    //         assembler->getRelocationTable()->push_back(
    //             new RelocationTableEntry{
    //                 assembler->getActiveSection(),
    //                 assembler->getActiveSection()->counter + 3,
    //                 addend,
    //                 "HIPO-16-PAYLOAD",
    //                 symbol
    //             }
    //         );
    //     }
    //     else{
    //         return -1;
    //     }

    //     mi
    //         .setSourceRegister(MachineInstruction::getRegister(
    //                 operand->getArguments()[0]->getValue(assembler->getSymbolTable())))
    //         .setUpdateMode(MachineInstruction::UpdateMode::NONE)
    //         .setAddressMode(MachineInstruction::AddressMode::REGISTER_INDIRECT_OFFSET)
    //         .setPayload(payload);
    // }
    // else{
    //     return -1;
    // }
    // std::string intstruction = mi.getInstruction();

    std::string intstruction = getMachineInstruction(assembler).getInstruction();

    assembler->getActiveSection()->machineCode += intstruction;
    assembler->getActiveSection()->counter += getSize();
    return 0;
}

std::string OperandInstruction::getType(){
    return "#" + operand->getType() + "#";
}