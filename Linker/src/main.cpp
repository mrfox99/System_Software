#include <string>
#include <vector>
#include <regex>
#include <iostream>

#include "../inc/Linker.hpp"

int main(int argc, char *argv[]){
    std::vector<std::string> inputFiles;
    std::string outputFile;
    std::map<unsigned short, std::string> addressMap;
    std::string mode;

    std::smatch match;

    std::vector<std::string> arguments(argv + 1, argv + argc);
    
    for(auto it = arguments.begin(); it < arguments.end(); it++){
        if(*it == "-o"){
            if(outputFile.empty() && ++it < arguments.end()){
                outputFile = *it;
            }
            else{
                exit(1);
            }
        }
        else if(*it == "-hex" || *it == "-linkable"){
            if(mode.empty()){
                mode = (it->substr(1));
            }
            else{
                return -1;
            }
        }
        else if(std::regex_search(*it, match, std::regex("-place=([a-zA-Z_]+)@((0x)?[0-9A-F]+)"))){
            
            std::string section = match.str(1);
            unsigned int address = std::strtol(match.str(2).c_str(), nullptr, match.str(3)=="0x" ? 16 : 10);

            if(addressMap.find(address) == addressMap.end()){
                addressMap.insert(std::pair<unsigned short, std::string>(address, section));
            }
            else{
                return -1;
            }
        }
        else {
            inputFiles.push_back(*it);
        }
    }
    if(mode.empty()){
        return -1;
    }
    if(inputFiles.size() == 0){
        return -1;
    }
    if(outputFile.empty()){
        return -1;
    }
    //std::cout<<"Linker started"<<std::endl;
    Linker l(inputFiles, outputFile, addressMap, mode);
    int ret = l.link();
    //std::cout<<"Linker end"<<ret<<std::endl;
    exit(ret);
}