#include <iostream>
#include <fstream>
#include <bitset>

#include "../inc/Linker.hpp"
#include "../inc/Symbol.hpp"
#include "../inc/Section.hpp"
#include "../inc/Relocation.hpp"
#include "../inc/Part.hpp"

Linker::Linker(
        std::vector<std::string> inputFiles,
        std::string outputFile,
        std::map<unsigned short, std::string> addressMap,
        std::string mode
        )
:inputFiles(inputFiles), outputFile(outputFile),
addressMap(addressMap), mode(mode){
}

Linker::~Linker(){
    for(auto it: symbols){
        delete it.second;
    }
    for(auto it: sections){
        delete it.second;
    }
    for(auto it: relocations){
        delete it;
    }
}

int Linker::link(){

    int ret = 0;
    
    if(ret = loadFiles())
        return ret;

    std::cout << "Files loaded" << std::endl;

    if(ret = merge())
        return ret;

    std::cout << "Files merged" << std::endl;

    if(mode == "hex"){
        if(ret = generateHex())
            return ret;

        std::cout << "Hex generated" << std::endl;
    }
    else if(mode == "linkable"){
        if(ret = generateLinkable())
            return ret;
        std::cout << "Linkable generated" << std::endl;
    }
    else{
        return -1;
    }
        
    return 0;
}

int Linker::loadFiles(){
    std::string skip;
    std::fstream inFile;

    for(std::string inputFile: inputFiles){

        std::map<std::string, Symbol*> tmpLocalSymbols;
        std::map<std::string, Symbol*> tmpGlobalSymbols;
        std::vector<Relocation *> tmpRelocations;
        std::map<std::string, int> offsets;

        inFile.open(inputFile);

        inFile >> skip;


        inFile >> skip;
        unsigned int symbolCount = 0;
        inFile >> skip;
        inFile >> symbolCount;

        unsigned int sectionCount = 0;
        inFile >> skip;
        inFile >> sectionCount;

        unsigned int relocationCount = 0;
        inFile >> skip;
        inFile >> relocationCount;
        inFile >> skip;
        
        inFile >> skip;

        inFile >> skip;
        for(int i = 0; i < symbolCount; i++){
            Symbol* symbol= new Symbol();
            inFile >> skip;
            inFile >> symbol->name;
            
            inFile >> skip;
            inFile >> symbol->value;

            inFile >> skip;
            inFile >> symbol->scope;

            inFile >> skip;
            inFile >> symbol->type;

            inFile >> skip;
            inFile >> symbol->defined;

            inFile >> skip;
            inFile >> symbol->sectionName;
            
            if(symbol->scope == "Global"){
                auto it = symbols.find(symbol->name);
                if(it == symbols.end()){
                    tmpGlobalSymbols.insert(
                        std::pair<std::string, Symbol*>(
                            symbol->name, 
                            symbol)
                        );
                    symbols.insert(
                        std::pair<std::string, Symbol*>(
                            symbol->name, 
                            symbol)
                        );
                }
                else if (it->second->name != it->second->sectionName){
                    std::cout << "Multiple symble definition:" << symbol->name << std::endl;
                    return -1;
                }

            }
            else if(symbol->scope == "Local"){
                auto it = symbols.find(symbol->name);
                if(it == symbols.end()){
                    tmpLocalSymbols.insert(
                        std::pair<std::string, Symbol*>(
                            symbol->name, 
                            symbol)
                        );
                    symbol->name = inputFile + "#" + symbol->name;    
                    symbols.insert(
                        std::pair<std::string, Symbol*>(
                            symbol->name, 
                            symbol)
                        );
                }
                else{
                    std::cout << "Multiple symble definition" << std::endl;
                    return -1;
                }
            }
            
            inFile >> skip;
        }

        inFile >> skip;

        inFile >> skip;
        for(int i = 0; i < sectionCount; i++){

            std::string name;
            std::string machineCode;

            inFile >> skip;
            inFile >> name;

            inFile >> skip;
            inFile >> machineCode;
            if(machineCode == "//")
                machineCode = "";

            auto it = sections.find(name);
            if(it == sections.end()){

                offsets.insert(std::pair<std::string, int>(name, 0));
                sections.insert(std::pair<std::string, Section*>(name, new Section{name, machineCode, 0}));
            }
            else{
                offsets.insert(std::pair<std::string, int>(name, it->second->machineCode.size()/8));
                it->second->machineCode += machineCode;
            }
            inFile >> skip;

        }

        inFile >> skip;

        inFile >> skip;
        for(int i = 0; i < relocationCount; i++){
            Relocation *relocation = new Relocation();

            inFile >> skip;
            inFile >> relocation->sectionName;

            inFile >> skip;
            inFile >> relocation->offset;

            inFile >> skip;
            inFile >> relocation->addend;

            inFile >> skip;
            inFile >> relocation->type;

            inFile >> skip;
            inFile >> relocation->symbolName;

            relocations.push_back(relocation);
            tmpRelocations.push_back(relocation);
            
            inFile >> skip;
        }
        inFile >> skip;

        for(std::pair<std::string, Symbol*> pair: tmpLocalSymbols){
            if(pair.second->name != pair.second->sectionName){
                pair.second->value += offsets.find(pair.second->sectionName)->second;
            }
        }

        for(std::pair<std::string, Symbol*> pair: tmpGlobalSymbols){
            if(pair.second->name != pair.second->sectionName){
                pair.second->value += offsets.find(pair.second->sectionName)->second;
            }
        }

        for(Relocation *relocation: tmpRelocations){
            if(relocation->sectionName != "//"){
                relocation->offset += offsets.find(relocation->sectionName)->second;
            }
            auto it = tmpLocalSymbols.find(relocation->symbolName);
            if(it != tmpLocalSymbols.end()){
                relocation->symbolName = it->second->name;
            }
        }
        inFile.close();
    }

    for(Relocation *relocation: relocations){
        if(relocation->sectionName == "//"){
            auto it = symbols.find(relocation->symbolName);
            if(it != symbols.end()){
                Symbol *symbol = it->second;
                if(symbol->scope == "Global"){
                    relocation->sectionName = symbol->sectionName;
                }
            }
        }
    }
    return 0;
}

int Linker::merge(){
    for(auto i = relocations.begin(); i != relocations.end();){
        Relocation *relocation = *i;

        auto it = symbols.find(relocation->symbolName);
        if(it == symbols.end()){
            i++;
            continue;
        }
        auto its = sections.find(relocation->sectionName);
        if(its == sections.end()){
            i++;
            continue;
        }
        Symbol *symbol = it->second;
        Section *section = its->second;
        if(symbol->type != "Absolute"){
            i++;
            continue;
        }
        std::bitset<16> payload;
        if(relocation->type == "HIPO-16-PAYLOAD"){
            payload = symbol->value + relocation->addend;
        }
        else if(relocation->type == "HIPO-16PC-PAYLOAD"){
            payload = symbol->value - relocation->offset + relocation->addend;
        }
        else if(relocation->type == "HIPO-16-DATA"){
            payload = symbol->value + relocation->addend;
            payload = (payload << 8) | (payload >> 8);
        }
        else{
            return -1;
        }
        section->machineCode.replace(relocation->offset * 8, 16, payload.to_string());
        relocations.erase(i++);

    }
    return 0;
}



int Linker::generateHex(){
    std::map<unsigned long, Section*> orderedSections;
    std::list<Section*> unorderedSections;

    for(std::pair<std::string, Section*> pair: sections){
        unorderedSections.push_back(pair.second);
    }

    for(std::pair<unsigned long, std::string> pair: addressMap){
        auto it = sections.find(pair.second);
        if(it != sections.end()){
            it->second->startAddress = pair.first;
            orderedSections.insert(std::pair<unsigned long, Section*>(
                it->second->startAddress, it->second)
                );
            unorderedSections.remove(it->second);
        }
    }
    unsigned long lastFreeAddress = 0;
    for(std::pair<unsigned long, Section*> pair: orderedSections){
        if(lastFreeAddress <= pair.second->startAddress){
            lastFreeAddress = pair.second->startAddress + pair.second->machineCode.size()/8;
        }
        else{
            std::cout << "Section overlap: " << pair.second->name << std::endl;
            return -1;
        }
    }
    for(Section* section: unorderedSections){
        if(!section->machineCode.empty()){
            section->startAddress = lastFreeAddress;
            orderedSections.insert(std::pair<unsigned long, Section*>(
                    lastFreeAddress, section)
                    );
            lastFreeAddress += section->machineCode.size()/8;
        }
    }
    if(lastFreeAddress > 1<<16){
        return -1;
    }
        
    for(Relocation *relocation: relocations){
        auto it = symbols.find(relocation->symbolName);
        if(it == symbols.end()){
            return -1;
        }
        auto its = sections.find(relocation->sectionName);
        if(its == sections.end()){
            return -1;
        }
        Symbol *symbol = it->second;
        Section *section = its->second;

        int symbolValue;
        if(symbol->type == "Absolute"){
            symbolValue = symbol->value;
        }
        else if(symbol->type == "Relocatable"){
            auto itss = sections.find(symbol->sectionName);
            if(itss == sections.end()){
                return -1;
            }
            symbolValue = itss->second->startAddress + symbol->value;
        }
        else{
            return -1;
        }

        std::bitset<16> payload;
        
        if(relocation->type == "HIPO-16-PAYLOAD"){
            payload = symbolValue + relocation->addend;
        }
        else if(relocation->type == "HIPO-16PC-PAYLOAD"){
            //std::cout << "sym val" << symbolValue<< "ofset" << relocation->offset<< "addend"<<relocation->addend << std::endl;
            payload = symbolValue - (section->startAddress + relocation->offset) + relocation->addend;
        }
        else if(relocation->type == "HIPO-16-DATA"){
            payload = symbolValue + relocation->addend;
            payload = (payload << 8) | (payload >> 8);
        }
        else{
            return -1;
        }
        section->machineCode.replace(relocation->offset * 8, 16, payload.to_string());
    }

    std::ofstream outFile(outputFile);
    for(std::pair<unsigned long, Section*> pair: orderedSections){
        unsigned long sectionAddress = pair.second->startAddress;
        for(int i = 0; i < pair.second->machineCode.size(); i += 8 * 8){
            std::bitset<16> address = sectionAddress;
            outFile << generateHexFromBinary(address.to_string()) << ": ";
            //std::cout << pair.second->name << generateHexFromBinary(address.to_string()) <<std::endl;
            for(int j = 0; j < 8; j++){
                if(pair.second->machineCode.size() <= i + j * 8){
                    break;
                }
                outFile << generateHexFromBinary(pair.second->machineCode.substr(i + j * 8, 8)) << " ";
            }
            outFile << std::endl;
            sectionAddress += 8;
        }

    
    }
    outFile.close();
    return 0;
}
int Linker::generateLinkable(){
    std::ofstream elfFile(outputFile);

    elfFile << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;

    elfFile << "---------------------------------" << std::endl;
    elfFile << "NUMBER_OF_SYMBOLS: " << symbols.size() << std::endl;
    elfFile << "NUMBER_OF_SECTIONS: " << sections.size() << std::endl;
    elfFile << "NUMBER_OF_RELOCATIONS: " << relocations.size() << std::endl;
    elfFile << "---------------------------------" << std::endl;

    elfFile << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    
    elfFile << "---------------------------------" << std::endl;
    for(std::pair<std::string, Symbol*> pair: symbols){
        if(pair.second->scope == "Global" ||
            (pair.second->scope == "Local" && 
            pair.second->type == "Relocatable")){
            elfFile << "SYMBOL_NAME: " << pair.second->name << std::endl;
            elfFile << "SYMBOL_VALUE: " << pair.second->value << std::endl;
            elfFile << "SYMBOL_SCOPE: " << pair.second->scope << std::endl;
            elfFile << "SYMBOL_TYPE: " << pair.second->type << std::endl;
            elfFile << "SYMBOL_DEFINED: " << pair.second->defined << std::endl;
            elfFile << "SYMBOL_SECTION_NAME: " << pair.second->sectionName << std::endl;
            elfFile << "---------------------------------" << std::endl;
        }
    }

    elfFile << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;

    elfFile << "---------------------------------" << std::endl;
    for(std::pair<std::string, Section*> pair: sections){
        elfFile << "SECTION_NAME: " << pair.second->name << std::endl;;
        elfFile << "SECTION_DATA: " << (pair.second->machineCode.empty()? "//" : pair.second->machineCode) << std::endl;
        elfFile << "---------------------------------" << std::endl;
    }
    elfFile << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;

    elfFile << "---------------------------------" << std::endl;
    for(Relocation *relocation: relocations){
        elfFile << "RELOCATION_SECTION_NAME: " << relocation->sectionName << std::endl;;
        elfFile << "RELOCATION_OFFSET: " << relocation->offset << std::endl;;
        elfFile << "RELOCATION_ADDEND: " << relocation->addend << std::endl;;
        elfFile << "RELOCATION_TYPE: " << relocation->type << std::endl;;
        elfFile << "RELOCATION_SYMBOL_NAME: " << relocation->symbolName << std::endl;
        elfFile << "---------------------------------" << std::endl;
    }

    elfFile << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;

    return 0;
}


std::string Linker::generateHexFromBinary(std::string binary){
    std::string hex = "";
    for(int i = 0; i < binary.size(); i += 4){
        std::string tmp = binary.substr(i, 4);
        if(tmp == "0000" || tmp == "000" || tmp == "00" || tmp == "0"){
            tmp = "0";
        }
        else if(tmp == "0001"){
            tmp = "1";
        }
        else if(tmp == "0010" || tmp == "001"){
            tmp = "2";
        }
        else if(tmp == "0011"){
            tmp = "3";
        }
        else if(tmp == "0100" || tmp == "010" || tmp == "01"){
            tmp = "4";
        }
        else if(tmp == "0101"){
            tmp = "5";
        }
        else if(tmp == "0110" || tmp == "011"){
            tmp = "6";
        }
        else if(tmp == "0111"){
            tmp = "7";
        }
        else if(tmp == "1000" || tmp == "100" || tmp == "10" || tmp == "1"){
            tmp = "8";
        }
        else if(tmp == "1001"){
            tmp = "9";
        }
        else if(tmp == "1010" || tmp == "101"){
            tmp = "A";
        }
        else if(tmp == "1011"){
            tmp = "B";
        }
        else if(tmp == "1100" || tmp == "110" || tmp == "11"){
            tmp = "C";
        }
        else if(tmp == "1101"){
            tmp = "D";
        }
        else if(tmp == "1110" || tmp == "111"){
            tmp = "E";
        }
        else if(tmp == "1111"){
            tmp = "F";
        }
        hex +=tmp;
    }
    return hex;
}