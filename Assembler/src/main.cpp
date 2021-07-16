#include <string>
#include <vector>
#include <iostream>

#include "../inc/Assembler.hpp"

int main(int argc, char* argv[]){

    std::string inputFile;
    std::string outputFile;

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
        else {
            if(inputFile.empty()){
                inputFile = *it;
            }
            else{
                exit(1);
            }
        }
    }

    Assembler a(inputFile, outputFile);
    int ret = a.assemble();
    exit(ret);
}
