#include <string>

struct Symbol;

struct Section{
    std::string name;
    std::string machineCode;
    unsigned long startAddress;
};
