#include <iostream>
#include <fstream>
#include <vector>

#define DEBUG 1
#if DEBUG 
    #define println(x) std::cout << x << std::endl;
    #define print(x)   std::cout << x;
#else
    #define println(x)
    #define print(x)
#endif

template <typename T> class HashSet {
    private:
        std::vector<T> data;
    public:
    //Constructors
        HashSet(){};
        HashSet(std::vector<T> x) {
            for (int i = 0; i < x.size(); i++) this->data.add(x[i]);
        }
    //Methods
        void add   (T   x) {
            if (!isHere(x)) this->data.push_back(x);
        }
        void remove(int i) {
            if(i <= this->data.size()) this->data.erase(this->data.begin()+i);
        }
        int  find  (T   x) {
            if (!isHere(x)) println(std::string(x + " not found")); return -1;
            for (int i = 0; i < this->data.size(); i++){
                if (this->data[i] == x) return i;
            }
        }
        bool isHere(T   x) {
            for (int i = 0; i < this->data.size(); i++){
                if (this->data[i] == x){
                    return true;
                } 
            }
            return false;
        }
        void sayAll() {
            for (int i = 0; i < this->data.size();i++) std::cout << this->data[i] << " ";
            std::cout << std::endl;
        }
        int  size  () {
            return this->data.size();
        };
        std::vector<T> getData(){
            return this->data;
        };
    //Operators
        T    operator[](int i){
            return this->data[i];
        }
        bool operator==(HashSet<T> x){
            return (this->data == x.data) ? true : false;
        }
};

template <typename T> T userInput() {
    T var;
    std::cin >> var;
    return var;
};

class Variable {
    public:
        std::string name = "";
        std::string type = "";
        std::string def  = "";
        bool operator==(Variable x){
            return (name == x.name) ? ((type == x.type) ? ((def == x.def) ? true : false) : false) : false;
        }
};

class Class {
    private:
        std::string          name;
        HashSet<Variable>    variables;
        HashSet<std::string> imports;
        HashSet<std::string> methods;
        std::string          inheritance;

    public:
    //Setters & Adders
        void setInheritance(std::string x){ this->inheritance = x;      }
        void setName       (std::string x){ this->name        = x;      }
        void addVariable   (Variable    x){ this->variables.add(x);     }
        void addMethod     (std::string x){ this->methods.add(x);       }
        void addImport     (std::string x){ this->imports.add(x);       }
    //Getters
        std::string getName()             { return this->name;          }
        std::string getInheritance()      { return this->inheritance;   }
        HashSet<Variable> getVariables()  { return this->variables;     }
        HashSet<std::string> getMethods() { return this->methods;       }
        HashSet<std::string> getImports() { return this->imports;       }
    //Methods
        bool isInheritance(){ return !(this->inheritance.size() == 0);  }
    //Operator help :P
        /*bool operator==(Class x){
            return 
                (this->name                == x.name                 ) ? (
                (this->inheritance         == x.inheritance          ) ? (
                (this->variables.getData() == x.variables.getData()  ) ? (
                (this->imports.getData()   == x.imports.getData()    ) ? (
                (this->methods.getData()   == x.methods.getData()    ) ?
                true:false):false):false):false):false
            ;
        }*/

};

class File {
private: 
    std::string name = "";
    std::string extension = ".txt";
    std::string fileName = "";

    bool isOpenable(){
        if((this->name != "" && this->extension != "") || this->fileName != ""){
            return true;
        }
        println(std::string(this->fileName + " cannot be opened"));
        return false;
    }
    bool exists(){
        std::fstream file(this->fileName);
        if(file){
            println(std::string(fileName + " already exists."));
            return true;
        }
        return false;
    }
    void setFileName (){
        this->fileName = this->name + this->extension;
    }
public:
//--------------------- TODO ---------------------//
//Setters
    void setName     (std::string x){ 
        this->name = x; 
        this->fileName = this->name + this->extension;
    }
    void setExtension(std::string x){
        this->extension = x;
        this->fileName = this->name + this->extension;
    }
    void setFileName (std::string x){
        this->fileName = x;
    }
//Builders
    bool buildNewFile(){
        //Checks
        if(!isOpenable()) return false;
        if(exists())      return false;

        std::ofstream file(this->fileName);

        file.close();
        //Succesful creation
        println(std::string(this->fileName + " created succesfully"));
        return true;
    }
    void buildClass();
//Readers
    std::string read(){
        std::ifstream file(this->fileName);
        std::string word = "";
        while (file >> word){
            // displaying content
            std::cout << word << std::endl;
        }
        return "";
    }
    void readFromUntil(std::string a,std::string b){
        std::ifstream file(this->fileName);
        std::string word;
        bool sno = false;
        while(file >> word){
            if(word == a) sno = true;
            if(sno)       println(word);
            if(word == b) sno = false;
        }
    }
    void readBetween(std::string a,std::string b){ //NO ANDA !!! >:(
        std::ifstream file(this->fileName);
        std::string word;
        bool sno = false;
        while(file >> word){
            if(word == a) file >> word; sno = true;
            if(sno)       println(word);
            if(word == b) sno = false;
        }
    }
//Writers
    void write(std::string x){
        std::ofstream file(this->fileName);
        file << x << std::endl;
    }
    void write(std::vector<std::string> x){
        std::ofstream file(this->fileName);
        for (int i = 0; i < x.size(); i++){
            file << x[i] << std::endl;
        }
    }
//Adders for external help files 
    void addDataStructure();
    void addVariableType();
//Class wirter
    bool writeClass(Class c){
    //Building file
        this->fileName  = c.getName();
        this->extension = ".java";
        this->setFileName();
        std::ofstream file(this->fileName);
    //Builder
        //Imports
        for (int i = 0; i < c.getImports().size(); i++) file << c.getImports()[i] << ";" << std::endl;
        file << std::endl;
        //Main structure
        file << "public class" << c.getName();
        if(c.isInheritance()) file << " extends " << c.getInheritance() << " {" << std::endl;
        
    //Success
        file.close();
        println("Class built succesfully");
        return true;
    };
};

int main(){
    File file;
    file.setFileName("dataTypes.txt");
    file.readFromUntil("Generic{","}");
    //file.readBetween("Primitive{","}");
    return 0;
}
