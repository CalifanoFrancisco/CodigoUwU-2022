#include <iostream>
#include <fstream>
#include <vector>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::fstream;
using std::ofstream;
using std::ifstream;

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
    :type(_type), name(_name), def(_def)
    {}

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
        file << "{" << std::endl;
        //Attributes
        std::string space = "    ";
        for (int i = 0; i < x.getAttributes().size(); i++)
            file << space << x.getAttributes()[i].type << " " << x.getAttributes()[i].name << ";" << std::endl;
        file << std::endl;
        //Methods
        for (int i = 0; i < x.getMethods().size(); i++){
            file << space << readUntil(x.getMethods()[i],')') << ";" << std::endl;
        }
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
            println(std::string(this->name + " already exists."));
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
    bool isAlreadyInFile(Class x) {     //WIP 
        std::ifstream file(this->name);
        std::string word;
        std::vector<std::string> buffer;
        bool out = false;
        while (file >> word) buffer.push_back(word);
        for (int i = 0; i < buffer.size(); i++){
            cout << "Is " << buffer[i][0] <<" == $ ?   ";
            if (buffer[i][0] == '$'){
                int c = 0;
                cout<<"SI"<<endl;
                std::string aux = buffer[i];
                cout << "Palabra a comparar " << aux << endl;
                for (int j = 0; j < x.name.size(); i++){ //Se queda encerrado adentro de D == A ? NO
                    cout << "Es " << aux[j+1] << " == " << x.name[j] << " ?";
                    if (aux[j+1] == x.name[j]){
                        c++;
                        cout<<"Si"<<endl;
                    }else{
                        cout<<"no"<<endl;
                    }
                }
                if (c == x.name.size()) out = true;
            }else{
                cout <<"no"<<endl;
            }
        }
        return false;
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
        std::fstream file(this->name);
        std::vector<std::string> buffer = this->copyFileIntoBuffer();
        std::string interface = "";
        interface += "&" + x.name + "{";
        for (int i = 0; i < x.getMethods().size(); i++) interface += readUntilParenthesis(x.getMethods()[i]) + ";";
        interface += "}";
        writeIntoBuffer(buffer, "@INTERFACE", interface);
        writeBufferIntoFile(buffer);

    }
    void addIntoHelpFile (Class     x) {
        std::fstream file(this->name);
        std::vector<std::string> buffer = this->copyFileIntoBuffer();
        std::string class_ = "";
        class_ += "$" + x.name + "(";
        for (int i = 0; i < x.getAllAttributes().size(); i++){
            class_ += x.getAllAttributes()[i].type + "-" + x.getAllAttributes()[i].name;
            if (i < x.getAllAttributes().size()-1) class_ += ",";
        }
        class_ += "){}";
        writeIntoBuffer(buffer, "@CLASS", class_);
        writeBufferIntoFile(buffer);
    }
    void addIntoHelpFile (Enum      x) {
        //Symbol %
    }
    bool isInFile(Class x){
        return this->isAlreadyInFile(x);
    }
};

//Interfaces work correctly :D
//Instead of using #TYPE #END_TYPE use a character for each type

int main () {
    /*HelpFile coso = HelpFile();
    Interface x;
    x.name = "COso";
    x.addMethod("public void coso(){ lol teo }");
    x.addMethod("public int  getChota(){return this.Chota}");
    coso.addIntoHelpFile(x);*/
    /*int num = 10;
    int*ptr = &num;
    cout << ptr  << endl;
    cout << *ptr << endl;*/

    Class a,b,c,d;
    a.name = "A"; b.name = "B";
    c.name = "C"; d.name = "D";
    a.addAttribute(Variable("Integer","edad"  ,"0"          ));
    b.addAttribute(Variable("String" ,"nombre","\"ricardo\""));
    c.addAttribute(Variable("float"  ,"num"   ,"20"         ));
    d.addAttribute(Variable("double" ,"num2"  ,"78"         ));
    c.setInheritance(&d);
    b.setInheritance(&c);
    a.setInheritance(&b);
    Interface x;
    x.name = "Coso";
    x.addMethod("public void coso(){ lol teo }");
    x.addMethod("public int  getChota(){return this.Chota}");

    HelpFile file = HelpFile();

    //file.addIntoHelpFile(a);
    //file.addIntoHelpFile(b);
    //file.addIntoHelpFile(c);
    //file.addIntoHelpFile(d);
    //file.addIntoHelpFile(x);
    cout << file.isInFile(a) << endl;

    cout<<"Success!"<<endl;
    return 0;

}
