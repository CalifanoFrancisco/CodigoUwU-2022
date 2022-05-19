#ifndef CLASS_H
#define CLASS_H
#include <vector>
#include <iostream>

struct Variable{
        std::string name;
        std::string type;
};

class Class{
private:
    std::string name;
    std::vector<Variable> variables;
    bool inheritance;
    std::string inheritanceName;
    std::vector<std::string> varTypes;
public:

    Class();
    //Class(std::string name,bool inheritance);
    std::vector<Variable> getVariables();
    std::string getVarType(int i);
    std::string getVarName(int i);
    void        addVariable();
    void        sayData();
    void        setVarTypes(std::vector<std::string> types);


};

#endif // CLASS_H
