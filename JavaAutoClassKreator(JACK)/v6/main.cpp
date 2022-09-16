#include <iostream>
#include <fstream>
#include <vector>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;
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

/*
Optimizaciones
getHashSet() ----------> return this->hashSet;
getHashSet(int index) -> return this->hashSet[index];
*/

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
    HashSet<T>(){
        this->head = NULL;
    }
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
    int size(){
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
    Variable(std::string _type = "",std::string _name = "",std::string _def = "empty")
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
    virtual HashSet<Variable> getAttributes() = 0;
    virtual HashSet<std::string> getImports() = 0;
    virtual HashSet<std::string> getMethods() = 0;
};

class Interface : public ClassDef {
private:
    std::vector<Interface> inheritances;
public:
    Interface(){
        this->inheritances.clear();
    }
    void addImport (std::string x) {
        this->imports.add(x);
    }
    void addMethod (std::string x) {
        this->methods.add(x);
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
            if (i < x.getAttributes().size() - 1) file << ",";
        }
        file << ";" << std::endl << "}" << std::endl;
        file.close();
    }

};

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
    void writeBufferIntoFile(std::vector<std::string> buffer) {
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
    int  countChars(std::string buffer,char _char){
        int out = 0;
        for (int i = 0; i < buffer.size(); i++) if (buffer[i] == _char) out++;
        return out;
    }
    void replaceCharacters(std::vector<std::string>&buffer,char replace, char replacement){
        for (int i = 0; i < buffer.size(); i++) {
            for (int j = 0; j < buffer[i].size(); j++){
                if (buffer[i][j] == replace)  buffer[i][j] = replacement;
            }
        }
    }
    void replaceCharacters(std::string             &buffer,char replace, char replacement){
        for (int i = 0; i < buffer.size(); i++) {
            if (buffer[i] == replace) buffer[i] = replacement;
        }
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

    void load(HashSet<Interface>&interfaces,HashSet<Class>&classes,HashSet<Enum>&enums){
        std::vector<std::string> buffer = this->copyFileIntoBuffer();

        for (int i = 0; i < buffer.size(); i++) {
            if (buffer[i][0] == '$') {
                Class aux;
                aux.name = this->readUntil(buffer[i], '(', 1);
                if (!(buffer[i][aux.name.size() + 2] == ')')) {
                    int extraBuf = aux.name.size() + 2;
                    for (int e = 0; e < (this->countChars(buffer[i], ',') + 1); e++) {
                        Variable var;
                        var.type = readUntil(buffer[i], '-', extraBuf);
                        extraBuf += var.type.size() + 1;
                        if (e < this->countChars(buffer[i], ',')) {
                            var.name = readUntil(buffer[i], ',', extraBuf);
                        } else {
                            var.name = readUntil(buffer[i], ')', extraBuf);
                        }
                        extraBuf += var.name.size() + 1;
                        aux.addAttribute(var);
                    }
                }
                classes.add(aux);
            }
            if (buffer[i][0] == '&') {
                std::string info = "", method = "";
                while (buffer[i][0] != '}')
                { info += buffer[i] + " "; i++; }
                info += '}';
                //println("Interface: " + info);
                Interface auxInterface = Interface();
                auxInterface.name = readUntil(info, '(', 1);

                for (int e = auxInterface.name.size()+6; e < info.size();e++) {
                    method = readUntil(info,';',e);
                    e += method.size()+1;
                    if (method == "}") break;
                    auxInterface.addMethod(method);
                }
                interfaces.add(auxInterface);
            }
            if (buffer[i][0] == '%') {
                Enum aux;
                aux.name = this->readUntil(buffer[i], '{', 1);
                if (!((buffer[i][aux.name.size() + 2]) == '}')) {
                    int strtPos = aux.name.size() + 2;
                    for (int j = 0; j < (this->countChars(buffer[i], ',') + 1); j++) {
                        Variable var;
                        if (j < (this->countChars(buffer[i], ','))){
                            var.name = this->readUntil(buffer[i], ',', strtPos);
                        } else {
                            var.name = this->readUntil(buffer[i], '}', strtPos);
                        }
                        strtPos += var.name.size() + 1;
                        aux.addAttribute(var);
                    }
                }
                enums.add(aux);
            }
        }
    }
};

void testInit(){
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
    Interface x,y;
    x.name = "Coso";
    x.addMethod("public void coso(){ lol teo }");
    x.addMethod("public int  getChota(){return this.Chota}");
    y.name = "Leible";
    y.addMethod("public void leer()");
    y.addMethod("private boolean sexo()");
    y.addMethod("public HashMap<Integer,Float> matematicaasHijo()");
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
    file.addIntoHelpFile(y);

    JavaFile java;
    /*java.buildFile(a);
    java.buildFile(b);
    java.buildFile(c);
    java.buildFile(d);
    java.buildFile(E);*/
}

void printClasses(HashSet<Interface> interfaces) {
    cout << "Interfaces: " << endl;
    for(int i = 0; i < interfaces.size(); i++){
        cout << interfaces[i].name << " ";
        if (interfaces[i].hasInheritance()) {
            cout << "extends ";
            for (int e = 0; e < interfaces[i].getInterfaces().size(); e++) {
                cout << interfaces[i].getInterfaces()[e].name;
                if (e < interfaces[i].getInterfaces().size()-1) cout << ", ";
            }
        }
        cout << " {" << endl;
        for(int e = 0; e < interfaces[i].getMethods().size();e++) cout << "    "<<interfaces[i].getMethods()[e] << endl;
        cout << "}" << endl << endl;
    }
}
void printClasses(HashSet<Class>        classes) {
    cout << "Classes: " << endl;
    for(int i = 0; i < classes.size(); i++){
        cout << classes[i].name << " {" <<endl;
        for(int e = 0; e < classes[i].getAttributes().size(); e++) cout << "    " << classes[i].getAttributes()[e].toString() << endl;
        for(int e = 0; e < classes[i].getMethods().size();    e++) cout << "    " << classes[i].getMethods()[e] << endl;
        cout << "}" << endl << endl;
    }
}
void printClasses(HashSet<Enum>           enums) {
    cout << "Enums: " << endl;
    for(int i = 0; i < enums.size(); i++){
        cout << enums[i].name << " {" <<endl;
        for(int e =0; e < enums[i].getAttributes().size();e++) cout << "    " <<enums[i].getAttributes()[e].name << endl;
        cout << "}" << endl << endl;
    }
}

template <typename T> T input() {
    T out;
    std::cin >> out;
    return out;
}

Interface buildInterface (HashSet<Interface> interfaces) {
    Interface newInterface;
    std::cout << "Interface name: ";
    newInterface.name = input<std::string>();
    while (true) {
        std::cout << "> ";
        std::string command = input<std::string>();
        if (command ==           "help") { 
            std::cout << "help          " << std::endl;
            std::cout << "exit          " << std::endl;
            std::cout << "addInheritance" << std::endl;
            std::cout << "addMethod     " << std::endl;
            std::cout << "name          " << std::endl;
        }
        if (command ==           "exit") { 
            break; 
        }
        if (command == "addInheritance") {
            std::cout << "Available interfaces // type END to quit" << std::endl;
            printClasses(interfaces);
            bool isInFile = false, inheritanceLoop = true;
            while (inheritanceLoop) {
                std::string inheritance = input<std::string>();
                if (inheritance == "END") inheritanceLoop = false;
                for (int i = 0; i < interfaces.size(); i++) {
                    if (inheritance == interfaces[i].name) {
                        newInterface.addInheritance(interfaces[i]);
                        isInFile = true;
                        inheritanceLoop = false;
                        std::cout << "Inherited " << interfaces[i].name << " successfully" << std::endl;
                    }
                }
                if (!isInFile) std::cout << "Interface " << inheritance << " does not exist" << std::endl;
            }
        }
        if (command ==      "addMethod") {
            std::cout << "Write your method, to end it write \"END\"." << std::endl;
            std::string method = "";
            while (true) {
                std::string inp = input<std::string>();
                if (inp == "END") break;
                method += inp + " ";
            }
            std::cout << "Your method is: " << method << endl;
            newInterface.addMethod(method);
        }
        if (command ==           "name") {
            newInterface.name = input<std::string>();
        }
    }
    return newInterface;
    
}
Class     buildClass     (HashSet<Class>        classes) {
    Class newClass;
    std::cout << "Class name: ";
    newClass.name = input<std::string>();
    while (true) {
        std::cout << "> ";
        std::string command = input<std::string>();
        if (command == "setInheritance") {}
        if (command ==      "addMethod") {}
        if (command ==   "addAttribute") {}
        if (command ==           "name") {}
        if (command == "addInheritance") {}
        if (command ==           "help") {}
    }
}

int main () {
    HashSet<Enum>           enums = HashSet<Enum>();
    HashSet<Class>        classes = HashSet<Class>();
    HashSet<Interface> interfaces = HashSet<Interface>();

    testInit();

    HelpFile file = HelpFile();
    file.load(interfaces,classes,enums);

    for ( ; ; ) {
    std::cout << "1. Create new class"      << std::endl;
    std::cout << "2. Create new interface"  << std::endl;
    std::cout << "3. Create new enum"       << std::endl;
    switch (input<int>()) {
    case 1:
        break;
    case 2:
        interfaces.add(buildInterface(interfaces));
        printClasses(interfaces);
        break;
    case 4:
        return 0;
        break;
    default:
        return 0;
        break;
    }}

    //printClasses(interfaces);
    //printClasses(classes);
    //printClasses(enums);

    cout<<"Success!"<<endl;
    return 0;

}

/* Economia:
//   {@} Mercados tradicionales y nose
//   {@}
*/
