#include "Class.h"
#include <iostream>
#include <vector>

/*struct Variable{
        std::string name;
        std::string type;
};*/

/*Class::Class(){
    this->name="NotSpecified";
    this->inheritance=0;
    this->inheritanceName="";
    this->variables;
}*/
Class::Class(){
    //Declare name
    std::string className;
    bool inheritance_=false;
    std::cout<<"Class name: ";      std::cin>>className;
    this->name=className;

    //Declare inheritance
    bool inheritanceLoop=true;
    while(inheritanceLoop){
        std::cout<<"Inheritance? 0/1 "; std::cin>>inheritance_;
        switch(inheritance_){
            case 0:
                inheritanceLoop=0;
                this->inheritance=0;
            break;
            case 1:
                std::string input;
                std::cout<<"Class descendance? "<<std::endl;
                std::cin>>input;
                this->inheritance=1;
                this->inheritanceName=input;
                inheritanceLoop=0;
            break;
            //default: std::cout<<"Invalid input >:("<<std::endl; break;
        }
    }

    //Initialize vector
    this->variables;
}

void Class::addVariable(){
    bool menu=1;
    std::string InputVarType,InputVarName;
    std::cout<<"Variable name: "<<std::endl;
    std::cin>>InputVarName;
    while(menu){
        std::cout<<"Variable type: "<<std::endl;
        std::cin>>InputVarType;
        int aux=0;
        for(int i=0;i<this->varTypes.size();i++){
            if(InputVarType!=this->varTypes[0]){   aux++;  }
        }
        if(aux==this->varTypes.size()){
            std::cout<<"Invalid dataType, try again"<<std::endl;
        }else{
            Variable aux;
            aux.name=InputVarName;
            aux.type=InputVarType;
            this->variables.push_back(aux);
            std::cout<<"@ "<<aux.type<<" "<<aux.name<<" created."<<std::endl;
            menu=false;
        }
    }

}

void Class::sayData(){
    std::cout<<"# Current data "<<std::endl;
    std::cout<<"Class name: "<<this->name<<std::endl;
    if(this->inheritance){
        std::cout<<"Inheritance: "<<this->inheritanceName<<std::endl;
    }
    for(int i=0;i<this->variables.size();i++){
        std::cout<<variables[i].type<<" "<<variables[i].name<<"; "<<std::endl;
    }
}

void Class::setVarTypes(std::vector<std::string> types){
    this->varTypes=types;
}
