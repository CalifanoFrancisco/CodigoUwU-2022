#include <iostream>
#include <fstream>
#include <vector>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::fstream;     //Read & write
using std::ofstream;    //Write & build
using std::ifstream;    //Read only

#define DEBUG 1
#if DEBUG
    #define println(x) std::cout << x << std::endl
    #define print(x)   std::cout << x
#else
    #define println(x)
    #define print(x)
#endif


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
    Variable(std::string _type = "",std::string _name = "",std::string _def = "")
    :type(_type), name(_name), def(_def){}

    std::string toString(){
        return this->type + " " + this->name + " = " + this->def + ";";
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
public:
    void addImport (std::string x) {
        this->imports.add(x);
    }
    void addMethod (std::string x) {
        this->methods.add(x);
        println(std::string("Method \"" + x + "\" added"));
    }
    void addAttribute (Variable x) {
        this->attributes.add(x);
    }
    HashSet<Variable> getAttributes () { return this->attributes;   }
    HashSet<std::string> getImports () { return this->imports;      }
    HashSet<std::string> getMethods () { return this->methods;      }
    bool hasInheritance() {
        return (this->inheritances.size() > 0);
    }
    bool operator==(Interface x) {
        return (this->name == x.name);
    }
    void addInheritance(Interface x){
        this->inheritances.push_back(x);
    }
    std::vector<Interface> getInterfaces(){
        return this->inheritances;
    }
};

class Class     : public ClassDef {
private:
    Class* inheritance = NULL;          //Java supports only one class inheritance per class
    HashSet<Interface> interfaces;      //Java supports multiple interface implementations
public:
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

    void setInheritance(Class*class_){
        Class*aux = new Class;
        aux = class_;
        this->inheritance = aux;
    }
    Class*getInheritance(){
        return this->inheritance;
    }
    bool hasInheritance(){
        return (this->inheritance != NULL);
    }

    void addInterface(Interface x){
        this->interfaces.add(x);
    }
    HashSet<Interface> getInterfaces(){
        return this->interfaces;
    }
    bool hasInterface(){
        return !(this->interfaces.size() == 0);
    }
    HashSet<Variable> getAllAttributes(){
        HashSet<Variable> output;
        for (int i = 0; i < this->attributes.size(); i++) output.add(this->attributes[i]);
        if (this->hasInheritance()){
            bool inheritanceLoop = this->hasInheritance();
            Class auxClass = *(this->getInheritance());
            while (inheritanceLoop) {
                for (int i = 0; i < auxClass.getAttributes().size(); i++) output.add(auxClass.getAttributes()[i]);
                inheritanceLoop = auxClass.hasInheritance();
                if (inheritanceLoop) auxClass = *(auxClass.getInheritance());
            }
        }
        return output;
    }

    bool operator==(Class x){
        return (x.name == this->name);
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
    bool operator==(Enum x){
        return (this->name == x.name);
    }
};

std::string readUntil(std::string input,char until){
    std::string output = "";
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == until) break;
        output += input[i];
    }
    return output + ')';
}

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

class JavaFile {
public:
    void buildFile (Interface x) {
        //Creating file
        std::ofstream file(x.name+".java");
        //Adding imports
        for (int i = 0; i < x.getImports().size(); i++) file << "import " << x.getImports()[i] << ";" << std::endl;
        file << std::endl;
        //Main structure
        file << "public interface " << x.name << " ";
        //  Inheritance
        if (x.hasInheritance()){
            file << "extends ";
            for (int i = 0; i < x.getInterfaces().size(); i++) {
                file << x.getInterfaces()[i].name;
                if (i < x.getInterfaces().size()-1) file << ",";
            }
            file << " ";
        }
        file << " { " << std::endl;
        //Attributes
        std::string space = "    ";
        for (int i = 0; i < x.getAttributes().size(); i++)
            file << space << x.getAttributes()[i].type << " " << x.getAttributes()[i].name << ";" << std::endl;
        file << std::endl;
        //Methods
        for (int i = 0; i < x.getMethods().size(); i++){
            file << space << readUntil(x.getMethods()[i],')') << "; " << std::endl;
        }
        file << "}" << std::endl;
        file.close();
    }

    void buildFile (Class     x) {          //Faltan imports y metodos
        std::ofstream file(x.name + ".java");
        std::string space = "    ";
        // !!! Imports
        //Main structures
        file << "public class " << x.name << " ";
        if (x.hasInheritance()) file << "extends " << x.getInheritance()->name << " ";
        if (x.hasInterface()){
            file << "implements ";
            for (int i = 0; i < x.getInterfaces().size(); i++) {
                file << x.getInterfaces()[i].name;
                if (i < x.getInterfaces().size()-1) file << ", ";
            }
        }
        file << " {" << std::endl;
        //Attributes
        for (int i = 0; i < x.getAttributes().size(); i++)
            file << space << "private " << x.getAttributes()[i].type << " " << x.getAttributes()[i].name << ";" << std::endl;
        //Builders
        //Default
        file << space << "public " << x.name << "(){" << std::endl;
        if (x.hasInheritance()) file << space << space << "super();" << std::endl;
        for (int i = 0; i < x.getAttributes().size(); i++)
            file << space << space << "this." << x.getAttributes()[i].name << " = " << x.getAttributes()[i].def << ";" <<std::endl;
        file << space <<"}" << std::endl;
        //Builder
        //Parameters
        file << space << "public " << x.name << " (";
        for (int i = 0; i < x.getAllAttributes().size(); i++) {
            file << x.getAllAttributes()[i].type << " " << x.getAllAttributes()[i].name;
            if (i < x.getAllAttributes().size()-1) file << ", ";
        }
        file << "){" << std::endl;
        if (x.hasInheritance()) {
            file << space << space << "super(";
            for (int i = x.getAttributes().size(); i < x.getAllAttributes().size(); i++) {
                file << x.getAllAttributes()[i].name;
                if (i < x.getAllAttributes().size()-1) file << ", ";
            }
            file << ");" << std::endl;
        }
        for (int i = 0; i < x.getAttributes().size(); i++)
            file << space << space <<"this." << x.getAttributes()[i].name << " = " << x.getAttributes()[i].name << ";" << std::endl;
        file << space << "}" << std::endl << std::endl;
        //Class methods
        for (int i = 0; i < x.getMethods().size(); i++)
            file << space << x.getMethods()[i] << ";" << std::endl;
        //Interface methods

        //CLose file
        file << "}" << std::endl;
        file.close();
    }

    void buildFile (Enum      x) {
        std::ofstream file(x.name + ".java");
        std::string space = "   ";
        file << "public enum " << x.name << " {" << std::endl << space;
        for (int i = 0; i < x.getAttributes().size(); i++) {
            file << x.getAttributes()[i].name;
            if (i < x.getAttributes().size()-1) file << ",";
        }
        file << ";" << std::endl << "}" << std::endl;
        file.close();
    }

};

HashSet<Enum> enums;
HashSet<Class> classes;
HashSet<Interface> interfaces;

class HelpFile {
    // CLASS     $
    // INTERFACE &
    // ENUM      %
private:
    std::string name;
    std::vector<std::string> copyFileIntoBuffer () {
        std::fstream file(this->name);
        std::string word = "";
        std::vector<std::string> buffer;
        while (file >> word) buffer.push_back(word);
        return buffer;
    }
    void writeIntoBuffer (std::vector<std::string>&buffer,std::string category,std::string input) {
        std::vector<std::string> auxBuffer;
        for (int i = 0; i < buffer.size(); i++) {
            auxBuffer.push_back(buffer[i]);
            if (buffer[i] == (category)) {
                auxBuffer.push_back(input);
            }
        }
        buffer = auxBuffer;
    }
    void writeBufferIntoFile(std::vector<std::string>buffer) {
        std::fstream file(this->name);
        for (int i = 0; i < buffer.size(); i++) {
            file << buffer[i] << std::endl;
        }
    }
    bool checkFileHas(std::string input){
        std::ifstream file(this->name);
        std::string word;
        if (file){
            while (file >> word) {
                if (word == input) return true;
            }
            return false;
        }
        return false;
    }
    bool exists(){
        std::fstream file(this->name);
        if(file){
            //println(std::string(this->name + " already exists."));
            file.close();
            return true;
        }
        file.close();
        return false;
    }
    bool isEmpty(){
        std::fstream file(this->name);
        std::string word;
        int i = 0;
        for (; file >> word; i++){}
        bool empty = (i == 0);
        if (empty) println("HelpFile.txt is empty :(");
        return empty;
    }
    void build(){
        std::ofstream file(this->name);
        file.close();
    }
    bool isAlreadyInFile(Class     x) {
        std::ifstream file(this->name);
        std::vector<std::string> buffer;

        for (std::string word = ""; file >> word; ) buffer.push_back(word);

        for (int i = 0; i < buffer.size(); i++){
            if (buffer[i][0] == '$') {
                int c = 0;
                for (int j = 0; j < x.name.size(); j++) {
                    if (buffer[i][j+1] == x.name[j]) c++;
                }
                if (buffer[i][x.name.size()+1] == '(') c++;
                if (c == x.name.size()+1) return true;
            }
        }
        return false;
    }
    bool isAlreadyInFile(Interface x) {
        std::ifstream file(this->name);
        std::vector<std::string> buffer;

        for (std::string word = ""; file >> word; ) buffer.push_back(word);

        for (int i = 0; i < buffer.size(); i++){
            if (buffer[i][0] == '&') {
                int c = 0;
                for (int j = 0; j < x.name.size(); j++) {
                    if (buffer[i][j + 1] == x.name[j]) c++;
                }
                if (buffer[i][x.name.size() + 1] == '(') c++;
                if (c == x.name.size()+1) return true;
            }
        }
        return false;
    }
    bool isAlreadyInFile(Enum      x) {
        std::ifstream file(this->name);
        std::vector<std::string> buffer;

        for (std::string word = ""; file >> word; ) buffer.push_back(word);

        for (int i = 0; i < buffer.size(); i++){
            if (buffer[i][0] == '%') {
                int c = 0;
                for (int j = 0; j < x.name.size(); j++) {
                    if (buffer[i][j+1] == x.name[j]) c++;
                }
                if (buffer[i][x.name.size()+1] == '{') c++;
                if (c == x.name.size()+1) return true;
            }
        }
        return false;
    }
    std::string readUntil(std::string buffer, char until,int strtpos) {
        std::string out = "";
        for (int i = strtpos; i < buffer.size(); i++) {
            if (buffer[i] == until) break;
            out += buffer[i];
        }
        return out;
    }
    int countChars(std::string buffer,char _char){
        int out = 0;
        for (int i = 0; i < buffer.size(); i++) if (buffer[i] == _char) out++;
        return out;
    }
public:
    HelpFile(){
        this->name = "HelpFile.txt";
        if (!this->exists()) this->build();
        if (!this->isEmpty()) return;
        std::ofstream file(this->name);
        file << "@INTERFACE" << std::endl;
        file << "@CLASS"     << std::endl;
        file << "@ENUM"      << std::endl;
        file.close();
    }

    void addIntoHelpFile (Interface x) {
        if (this->isAlreadyInFile(x)) return;
        std::vector<std::string> buffer = this->copyFileIntoBuffer();
        std::string interface = "&" + x.name + "() { ";
        for (int i = 0; i < x.getMethods().size(); i++) interface += readUntilParenthesis(x.getMethods()[i]) + "; ";
        interface += " }";
        writeIntoBuffer(buffer, "@INTERFACE", interface);
        writeBufferIntoFile(buffer);
    }
    void addIntoHelpFile (Class     x) {
        if (this->isAlreadyInFile(x)) return;
        std::vector<std::string> buffer = this->copyFileIntoBuffer();
        std::string class_ = "$" + x.name + "(";
        for (int i = 0; i < x.getAllAttributes().size(); i++){
            class_ += x.getAllAttributes()[i].type + "-" + x.getAllAttributes()[i].name;
            if (i < x.getAllAttributes().size()-1) class_ += ",";
        }
        class_ += "){}";
        writeIntoBuffer(buffer, "@CLASS", class_);
        writeBufferIntoFile(buffer);
    }
    void addIntoHelpFile (Enum      x) {
        if (this->isAlreadyInFile(x)) return;
        std::vector<std::string> buffer = this->copyFileIntoBuffer();
        std::string enum_ = "%" + x.name + "{";
        for (int i = 0; i < x.getAttributes().size(); i++){
            enum_ += x.getAttributes()[i].name;
            if (i < x.getAttributes().size()-1) enum_ += ",";
        }
        enum_ += "}";
        writeIntoBuffer(buffer, "@ENUM", enum_);
        writeBufferIntoFile(buffer);
    }

    void loadInterfaces(){
        std::vector<std::string> buffer = this->copyFileIntoBuffer();
        for (int i = 0; i < buffer.size(); i++) {
            if (buffer[i][0] == '&') {
                std::string info = "";
                while (buffer[i][0] != '}') { info += buffer[i] + " "; i++; } info += '}';
                println("Interface: " + info);

                Interface auxInterface;
                auxInterface.name = readUntil(info, '(', 1);
                println("Name: " + auxInterface.name);

                std::string method = "";
                    
                for (int e = auxInterface.name.size()+6; e < info.size();e++) {
                    method = readUntil(info,';',e);
                    e += method.size()+1;
                    if (method == "}") break;
                    auxInterface.addMethod(method);
                }
                println("aaaa");    
                //PORQUE NO ANDA LA PUTA MADRE LO ESTOY AÑADIENDO NO ENTENDES TENES ONCE AÑOS PEDAZO DE PELOTUDO LA RECALCADA CONCHA DE TU REPUTSIMA MADRE QUE TE REMIL PARIO LA CONCHA DE LA SAN PUTA DIOS COMO ODIO C++ Y SU CREOADOR Y JAVA Y TODO LA REPUTA MADRE
                for (int p = 0; p < auxInterface.getMethods().size(); p++) { ///// CULPA DE MACRI
                    cout << auxInterface.getMethods()[i] << endl;
                }
                println("end") ;
            }

        }
    }
};

int main () {


    Class a,b,c,d,E;
    a.name = "Coso"; b.name = "B"; E.name = "E";
    c.name = "C"; d.name = "D";
    a.addAttribute(Variable("Integer","edad"  ,"0"          ));
    b.addAttribute(Variable("String" ,"nombre","\"ricardo\""));
    c.addAttribute(Variable("float"  ,"num"   ,"20"         ));
    d.addAttribute(Variable("double" ,"num2"  ,"78"         ));
    E.addAttribute(Variable("Persona","persona","new Persona()"));
    c.setInheritance(&d);
    b.setInheritance(&c);
    a.setInheritance(&b);
    E.setInheritance(&a);
    Interface x;
    x.name = "Coso";
    x.addMethod("public void coso(){ lol teo }");
    x.addMethod("public int  getChota(){return this.Chota}");
    Enum e;
    e.name = "Color";
    e.addAttribute(Variable("","ROJO",""));
    e.addAttribute(Variable("","AMARILLO",""));

    HelpFile file = HelpFile();

    file.addIntoHelpFile(a);
    file.addIntoHelpFile(a);
    file.addIntoHelpFile(b);
    file.addIntoHelpFile(c);
    file.addIntoHelpFile(d);
    file.addIntoHelpFile(x);
    file.addIntoHelpFile(x);
    file.addIntoHelpFile(e);
    file.addIntoHelpFile(e);

    JavaFile java;
    /*java.buildFile(a);
    java.buildFile(b);
    java.buildFile(c);
    java.buildFile(d);
    java.buildFile(E);*/
    file.loadInterfaces();

    cout<<"Success!"<<endl;
    return 0;

}

/* Economia:
//   {@} Mercados tradicionales y nose
//   {@}
*/
