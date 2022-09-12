#include <iostream>
#include <fstream>
#include <vector>
using std::cout;
using std::endl;
using std::cin;

template <typename T> class HashSet {
private:
    T         dato;
    HashSet<T>*next;
    HashSet<T>*head = NULL;
    bool isHere(T e) {
        for (HashSet<T>*current = head; current != NULL; current = current->next){
            if (current->dato == e) return true;
        }
        return false;
    }
    bool inBounds(int i) {
        if (i < 0 || i > this->size()) return false;
        return true;
    }
public:
    void add(T x) {
        if(isHere(x)) return;

        HashSet<T>*newNode = new HashSet<T>;
        newNode->dato = x;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            return;
        }
        for (HashSet<T>*current = head; current != NULL; current = current->next) {
            if (current->next == NULL) {
                current->next = newNode;
                return;
            }
        }
    }
    T    operator[](int index) {
        if (!inBounds(index)) return T();
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
        int i = 0;
        for (HashSet<T>*current = head; current != NULL; i++) current = current->next;
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

class Variable {
public:
    std::string type = "";
    std::string name = "";
    std::string def  = "";

    bool operator== (Variable x) {
        return (this->name == x.name);
    }
};

class ClassDef {
public:
    HashSet<std::string> imports,methods;
    HashSet<Variable>    attributes;
    std::string name;

    void setName (std::string _name) {
        if (!_name.size() == 0) this->name = _name;
    }

    virtual void addAttribute(Variable x) = 0;
    virtual void addImport(std::string x) = 0;
    virtual void addMethod(std::string x) = 0;
    virtual HashSet<Variable> getAttributes()=0;
    virtual HashSet<std::string> getImports()=0;
    virtual HashSet<std::string> getMethods()=0;

};

class Interface : public ClassDef {
private:
    std::vector<Interface> inheritances;
    bool inBounds(int index){
        if (index < 0 || index >= this->inheritances.size()) return false;
        return true;
    }
public:
    void addImport (std::string x) {}
    void addMethod (std::string x) {}
    void addAttribute (Variable x) {}
    HashSet<Variable> getAttributes () { return this->attributes;   }
    HashSet<std::string> getImports () { return this->imports;      }
    HashSet<std::string> getMethods () { return this->methods;      }
    bool hasInheritance() {
        return (this->inheritances.size() > 0);
    }
    /*std::string getInheritanceName(int index){
        //if (!inBounds(index)) return "";
        return this->inheritances[index].name;
    }
    std::vector<std::string> getInheritanceAttributes(int index){
        //if (!inBounds(index)) return HashSet<std::string>;
        return this->inheritances[index].attributes;
    }
    HashSet<std::string> getInheritanceMethods(int index){
        //if (!inBounds(index)) return HashSet<std::string>;
        return this->inheritances[index].methods;
    }*/
    bool operator==(Interface x) {
        return (this->name == x.name);
    }
};

class Class     : public ClassDef {
private:
    Class* inheritance = NULL;          //Java supports only one class inheritance per class
    HashSet<Interface> interfaces;      //Java supports multiple interface implementations
public:
    Class(){}
    void addAttribute (Variable x) {
        this->attributes.add(x);
    }
    void addImport (std::string x) {
        this->imports.add(x);
    }
    void addMethod (std::string x) {
        this->methods.add(x);
    }
    HashSet<Variable> getAttributes () {
        return this->attributes;
    }
    HashSet<std::string> getImports () {
        return this->imports;
    }
    HashSet<std::string> getMethods () {
        return this->methods;
    }
    bool hasInheritance () {
        return !(inheritance == NULL);
    }
    Class*getInheritance() {
        if (!hasInheritance()) return NULL;
        return this->inheritance;
    }
};

class Enum      : public ClassDef {
public:
    void addAttribute (Variable x) {
        this->attributes.add(x);
    }
    void addImport (std::string x) {}
    void addMethod (std::string x) {}
    HashSet<Variable> getAttributes () { return this->attributes;   }
    HashSet<std::string> getImports () { return this->imports;      }
    HashSet<std::string> getMethods () { return this->methods;      }
};

std::string readUntilParenthesis(std::string input){
    std::string output;
    for (int i = 0; i < input.size(); i++) {
        if (input[i]==')') break;
        output+=input[i];
    }
    return output + ')';
}
std::string toUpperCase(std::string input){
    for (int i = 0; i < input.size(); i++) {
        if (islower(input[i])) input[i] -= 32;
    }
    return input;
}

void buildFile (Interface x) {
    //Creating file
    std::fstream file(x.name+".txt");
    //Adding imports
    for (int i = 0; i < x.getImports().size(); i++)
        file << "import " << x.getImports()[i] << ";" << std::endl;
    file << std::endl;
    //Main structure
    file << "public interface " << x.name << " ";
    //  !TODO
    if (x.hasInheritance()){
        file << "extends ";
        /*for (int i = 0; i < x.getInheritances().size(); i++){
            file << x.getInheritances()[i]
            if (i < x.getInheritances().size()-1) file << ",";
        }*/
    }
    file << "{" << std::endl;
    //Attributes
    std::string space = "    ";
    for (int i = 0; i < x.getAttributes().size(); i++) 
        file << space << x.getAttributes()[i].type << " " << x.getAttributes()[i].name << ";" << std::endl;
    file << std::endl;
    //Methods
    for (int i = 0; i < x.getMethods().size(); i++)
        file << space << readUntilParenthesis(x.getMethods()[i]) << ";" << std::endl;
    file << "}" << std::endl;
    file.close();
}

void buildFile (Class     x) { }

void buildFile (Enum      x) {
    std::fstream file(x.name + ".java");
    std::string space = "   ";
    file << "public enum " << x.name << " {" << std::endl;
    file << space;
    for (int i = 0; i < x.getAttributes().size(); i++) {
        file << x.getAttributes()[i].name;
        if (i < x.getAttributes().size()-1) file << ",";
    }
    file << ";" << std::endl;
    file << "}" << std::endl;
    file.close();
}

//WIP
// Hacer q una clase pueda contener otra clase dentro (herencia) asi se hacen los constructores
// default mas completos

// Hacer q una interfaz pueda contener a otra interfaz dentro, permite multiple herencia



int main () {

    cout<<"Success!"<<endl;
    return 0;

}
