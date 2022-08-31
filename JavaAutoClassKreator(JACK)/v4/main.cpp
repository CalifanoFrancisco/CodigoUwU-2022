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
                (this->name        == x.name       ) ? (
                (this->inheritance == x.inheritance) ? (
                (this->variables   == x.variables  ) ? (
                (this->imports     == x.imports    ) ? (
                (this->methods     == x.methods    ) ?
                true:false):false):false):false):false
            ;
        }*/

};

class File {
private: 
    std::string name = "";
    std::string extension = ".txt";
public:
//--------------------- WIP ---------------------//

    bool buildNewFile(){

        if(this->name == "") println("File has no name"); return false;

        std::string totalName = this->name + this->extension;

        std::ifstream file(totalName);

        if(file) println(std::string(totalName + " already exists.")); return false;
        
        return true;
    }
    
    void buildClass();
    void addDataStructure();
    void addVariableType();
 
};

int main(){
    HashSet<Class> clases;


    return 0;
}
