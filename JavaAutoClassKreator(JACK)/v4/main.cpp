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
    T         dato;
    HashSet<T>*next;
    HashSet<T>*head = NULL;
    bool isHere(T e){
        HashSet<T>*current = head;
        while (current != NULL) {
            if (current->dato == e) return true;
            current = current->next;
        }
        return false;
    }
    bool inBounds(int i){
        if (i < 0 || i > this->size()) return false;
        return true;
    }
public:
    void add(T x){
        if(isHere(x)) return;

        HashSet<T>*newNode = new HashSet<T>;
        newNode->dato = x;
        newNode->next = NULL;

        if(head == NULL){
            head = newNode;
            return;
        }

        HashSet<T>*current = head;
        while (current != NULL) {
            if (current->next == NULL) {
                current->next = newNode;
                return;
            }
            current = current->next;
        }
    }
    T    operator[](int index){
        if (index > size() || index < 0) return T();
        HashSet<T>*current = head;
        for(int i = 0;i < index; i++) current = current->next;
        return current->dato;
    }
    bool operator==(HashSet e){
        
        if (!inBounds(e.size())) return false;

        HashSet<T>*current = head;
        for (int i = 0; current != NULL; i++){
            if (current->dato != e[i]) return false;
            current = current->next;
        }
        return true;
    }
    int  size(){
        HashSet<T>*current = head;
        int i = 0;
        for (; current != NULL; i++) current = current->next;
        return i;
    }
    void remove(int index){

        if (!inBounds(index)) return;

        HashSet<T>*current = head;
        HashSet<T>*before  = NULL;
        for(int i = 0; current != NULL; i++){
            if (index == i){
                before->next = current->next;
                delete current;
                return;
            }
            before  = current;
            current = current->next;
        }
    } 
};

template <typename T> T userInput() {
    T var;
    std::cin >> var;
    return var;
};

class Class {
    private:
    
        class Variable {
        public:
            std::string name = "";
            std::string type = "";
            std::string def  = "";
            bool operator==(Variable x){
                return (name == x.name) ? ((type == x.type) ? ((def == x.def) ? true : false) : false) : false;
            }
        };
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
    std::string name      = "";
    std::string extension = "";
    std::string fileName  = "";
public:
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
            file.close();
            return true;
        }
        file.close();
        return false;
    }
    void setFileName (){
        this->fileName = this->name + this->extension;
    }
//public:
//Setters
    void setName     (std::string x){ 
        this->name = x; 
        this->setFileName();

    }
    void setExtension(std::string x){
        this->extension = x;
        this->setFileName();
    }
    void setFileName (std::string x){
        this->fileName = x;
    }
//Builders
    bool buildNewFile(){
        //Checks
        if(!isOpenable()) return false;
        //if(exists())      return false;
        //Creation
        std::ofstream file(this->fileName);
        //Succesful creation
        println(std::string(this->fileName + " created succesfully"));
        file.close();
        return true;
    }
//Finders
    bool isHere(std::string x){
        std::fstream file(this->fileName);
        std::string word = "";
        while(file >> word){
            if(word == x){
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }
//Readers
    std::string read(){
        std::ifstream file(this->fileName);
        std::string word = "",out = "";
        while (file >> word) out += word + " ";
        file.close();
        return "";
    }
    bool readFromUntil(std::string a,std::string b){
        //Checks
        if(!isHere(a)){ println(std::string(a + " not found")); return false; }
        if(!isHere(b)){ println(std::string(b + " not found")); return false; }

        std::ifstream file(this->fileName);
        std::string word;
        bool sno = false;
        while(file >> word){
            if(word == a) sno = true; 
            if(sno)       println(word);
            if(word == b) sno = false;
        }
        file.close();
        return true;
    }
    bool readBetween(std::string a,std::string b){
        //Checks
        if(!this->exists()) return false;
        if(!isHere(a)){ println(std::string(a + " not found")); return false; }
        if(!isHere(b)){ println(std::string(b + " not found")); return false; }
        //Builds file
        std::ifstream file(this->fileName);
        std::string word;
        //Reads
        bool sno = false;
        while(file >> word){
            if(word == a){  file >> word; sno = true;   }
            if(word == b){  file >> word; sno = false;  }
            if(sno)         println(word);
        }
        file.close();
        return true;
    }
//Writers
    void writeln(std::string x){
        std::ofstream file(this->fileName);
        file << x << std::endl;
        file.close();
    }
    void writeln(std::vector<std::string> x){
        std::ofstream file(this->fileName);
        for (int i = 0; i < x.size(); i++){
            file << x[i] << std::endl;
        }
        file.close();
    }
};

class JavaFile : public File {
private:
    std::string fltu(std::string input){ //First Letter To Uppercase
        if(islower(input[0])) input[0] -= 32;
        return input;
    }
public:
    void buildClass(Class c){

        std::string space = "    ";

        this->setName(c.getName());
        this->setExtension(".java");
    //If class already exists asks if it has to be overwritten
        if(this->exists()){     
            println("Class " + c.getName() + " already exists. Overwrite Y/N");
            std::string x = userInput<std::string>();
            if (x == "N" || x == "n") return;
        }
    //Creates and opens new file
        buildNewFile();
        std::ofstream file(c.getName() + ".java");
    //Adds imports
        for (int i = 0; i < c.getImports().size(); i++) file << c.getImports()[i] << std::endl; file << std::endl;
    //Main structure
        file << "public class " << c.getName() << " ";
        if (c.isInheritance()) file << "extends " << c.getInheritance();
        file << "{" << std::endl;
    //Variables
        for (int i = 0; i < c.getVariables().size(); i++) 
            file << space << c.getVariables()[i].type << " " << c.getVariables()[i].name << ";" << std::endl;
        file << std::endl;
        //file << space << c.getVariables()[i].type << " " << c.getVariables()[i].name /*<< " = " << c.getVariables()[i].def*/ << ";" << std::endl;
    //Constructors
    //Default
        file << space << "public " << c.getName() << "(){" << std::endl;
        if (c.isInheritance()) file << space << space << "super();" << std::endl;
        for (int i = 0; i < c.getVariables().size(); i++)
            file << space << space << "this." << c.getVariables()[i].name << " = " << c.getVariables()[i].def << ";" << std::endl;
        file << space << "}" << std::endl;
    //By parameters
        //Checks if its just a class that extends other one w no new values
        if (c.isInheritance() && c.getVariables().size() == 0) {

        } else {
            file << space << "public " << c.getName() << "(";
            for (int i = 0; i < c.getVariables().size(); i++){
                file << c.getVariables()[i].type << " " << c.getVariables()[i].name;
                if (i < c.getVariables().size()-1) file << ",";
            }
            file << "){" << std::endl;
            for (int i = 0; i < c.getVariables().size(); i++)
                file << space << space << "this." << c.getVariables()[i].name << " = " << c.getVariables()[i].name << ";" << std::endl;
            file << space << "}"  << std::endl;
        }
    //Setters & getters
        //Setters
        for (int i = 0; i < c.getVariables().size(); i++)
            file << space << "public void set" << fltu(c.getVariables()[i].name) << "(" << c.getVariables()[i].type << " " << c.getVariables()[i].name << "){ this." << c.getVariables()[i].name << " = " << c.getVariables()[i].name << ";" << std::endl;
        //Getters
        for (int i = 0; i < c.getVariables().size(); i++)
            file << space << "public " << c.getVariables()[i].type << " get" << c.getVariables()[i].name << "(){ return this." << c.getVariables()[i].name << "; }" << std::endl;
        
    //Methods
        //for (int i = 0; i < c.getMethods().size(); i++)   //idk what syntax methods will have

    //Closing file
        file << "}" << std::endl;
        file.close();
    }
};

class HelpFile : public File {

};

//Crear clase padre FILE y clases hijo JavaFile y helpFiles
//class JavaFile : private File {}  //Sintaxis

//struct Variable adentro de Class

int main(){
    File file;
    file.setFileName("dataTypes.txt");
    //file.readFromUntil("#GENERIC","#END_GENERIC");
    file.readBetween("#GENERIC","#END_GENERIC");
    return 0;
}
