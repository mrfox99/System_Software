#include <string>

struct Section;

struct Symbol{
    std::string name;
    unsigned short value;
    std::string scope;
    std::string type;
    bool defined;
    std::string sectionName;
};
