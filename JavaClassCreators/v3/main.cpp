#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

string extensionArchivo = ".txt";
// ''

struct Variable {
    std::string dataType = "" ;
    std::string dataName = "" ;
    std::string totalDeclaration = "" ;
};

struct DataTypesInfo{
    std::string dataType;
    std::string initializer;
    std::string imports;
};

class Clase{
public:
    std::vector<Variable> variables;
    std::string nombre;
    std::string herencia = "" ;
    std::vector<string> imports;
    std::vector<string> metodos;

    void addVariable(Variable    _var){
        this->variables.push_back(_var);
    }
    void addMetodos(string _metodo){
        this->metodos.push_back(_metodo);
    }

    void addVariable(string _dataType,string _dataName){
        Variable var;
        var.dataName = _dataName;
        var.dataType = _dataType;
        this->variables.push_back(var);
    }

    void addImport  (string _import){
        int e=0;
        for(int i=0;i<imports.size();i++){
            if(imports[i]!=_import){ e++; }
        }
        if(e==imports.size()){
            this->imports.push_back(_import);
        }
    }
    void sayAllDeclarations(){
        for(int i=0;i<imports.size();i++){    cout<<imports[i]<<endl;   }

        for(int i=0;i<variables.size();i++){
            cout<<variables[i].totalDeclaration<<endl;
        }
    }

};

std::vector<Clase> clases;

std::vector<DataTypesInfo> inicializadores(){   //no lo uso lol

    std::vector<DataTypesInfo> out;
    DataTypesInfo aux;

    aux.dataType    = "LocalTime";
    aux.initializer = "LocalTime.now()";
    aux.imports     = "import java.time.LocalTime";
    out.push_back(aux);
    aux.dataType    = "LocalDate";
    aux.initializer = "LocalDate.now()";
    aux.imports     = "import java.time.LocalDate";
    out.push_back(aux);
    aux.dataType    = "LocalDateTime";
    aux.initializer = "LocalDateTime.now()";
    aux.imports     = "import java.time.LocalDateTime";
    out.push_back(aux);
    aux.dataType    = "ArrayList";
    aux.initializer = "new ArrayList<>()";
    aux.imports     = "import java.util.ArrayList";
    out.push_back(aux);
    aux.dataType    = "HashMap";
    aux.initializer = "new HashMap<>()";
    aux.imports     = "import java.util.HashMap";
    out.push_back(aux);
    aux.dataType    = "HashSet";
    aux.initializer = "new HashSet<>()";
    aux.imports     = "import java.util.HashSet";
    out.push_back(aux);

    /*
    aux.dataType    = ;
    aux.initializer = ;
    aux.imports     = ;
    out.push_back(aux);
    */
    return out;
}

string userInputString(){
    string aux;
    cin>>aux;
    return aux;
}

int userInputInt(){
    int i;
    cin>>i;
    return i;
}

void writeFile(Clase clase){
    ofstream file(clase.nombre+extensionArchivo);

    /*ofstream file;
    file.open(clase.nombre+extensionArchivo);*/
    string sangria = "      " ;
//Imports
    for(int i=0;i<clase.imports.size();i++){
        file << clase.imports[i] << ";" << endl;
    }
    file << endl << endl;
//
    file << "public class " + clase.nombre + " {" << endl;
//atributos
    for(int i=0;i<clase.variables.size();i++){
        file << sangria <<"private" <<clase.variables[i].dataType << " " << clase.variables[i].dataName << ";" <<endl;
    }
//constructores
    //default
    file << sangria << "public " << clase.nombre << "() {"<<endl;
    for(int i=0;i<clase.variables.size();i++){
        file << sangria << sangria << "this." << clase.variables[i].totalDeclaration << endl;
    }
    file << sangria << "}" << endl << endl;
    //por parametros
    file << sangria << "public " << clase.nombre << "(";
    for(int i=0;i<clase.variables.size();i++){
        file << clase.variables[i].dataType << " " << clase.variables[i].dataName;
        if(i<clase.variables.size()){     file << ",";    }
    }
    file << ") {" <<endl;
    for(int i=0;i<clase.variables.size();i++){
        file << sangria << sangria << "this." << clase.variables[i].dataName << " = " <<clase.variables[i].dataName << ";" << endl;
    }
    file << sangria << "}" << endl << endl;
//setters
    for(int i=0;i<clase.variables.size();i++){
        file << sangria;
        file << "public " << "void"                      << " set" << clase.variables[i].dataName;
        file << "("       << clase.variables[i].dataType << " i){"   ;
        file << " this."  << clase.variables[i].dataName << " = i; ";
        file << "}"       << endl;
    }
    file << endl;
//getters
    for(int i=0;i<clase.variables.size();i++){
        file << sangria;
        file << "public " << clase.variables[i].dataType << " get" << clase.variables[i].dataName << "(){";
        file << " return this." << clase.variables[i].dataName<< ";";
        file << " }" << endl;
    }
    file << endl;
//metodos
    for(int i=0;i<clase.metodos.size();i++){
        file << clase.metodos[i] << endl;
    }
    file << "}" << endl;
    file.close();
    println("Clase " + clase.nombre + " creada exitosamente :3");
}

/*std::string checkIsInVector(string in){
    std::vector<DataTypesInfo> aux = inicializadores();
    for(int i=0;i<aux.size();i++){
        if(int == aux[i].dataType){
            return string
        }
    }
}*/

void addInputs(Clase&clase){
    std::vector<std::string> out;
    clase.addImport("import java.util.Scanner;");
    clase.addMetodos("private static int    inputInt()    { return new Scanner(System.in).nextInt();    }");
    clase.addMetodos("private static String inputString() { return new Scanner(System.in).nextLine();   }");
    clase.addMetodos("private static float  inputFloat()  { return new Scanner(System.in).nextFloat();  }");
    clase.addMetodos("private static double inputDouble() { return new Scanner(System.in).nextDouble(); }");
}

void addEasyPrints(Clase&clase){
    clase.addMetodos("private static void println   (String i){ System.out.println(i); }");
    clase.addMetodos("private static void printlnErr(String i){ System.err.println(i); }");
    clase.addMetodos("private static void printErr  (String i){ System.err.print(i);   }");
    clase.addMetodos("private static void print     (String i){ System.out.print(i);   }");
}

void println(string i){ cout<<i<<endl;  }

Clase buildClase(){
    Clase clase;
    println("Nombre de la clase: ");
    clase.nombre = userInputString();
    println("Herencia? S/N");
    string temp = userInputString();
    if(temp=="S" || temp=="s" || temp=="Y" || temp=="y"){
        println("Inserte nombre de la herencia: ");
        clase.herencia = userInputString();
    }

    //println("Atributos,esciba ready para finalizar, toque cualquier tecla ");

    bool loop = true;

    while(loop){
        Variable aux;
        bool complexDataType = false;
        println("Tipo de dato: ");
        aux.dataType = userInputString();

        if(aux.dataType=="HashMap"  ){
            aux.dataType+="<";
            println("KeySet datatype: ");
            aux.dataType+=userInputString();
            aux.dataType+=",";
            println("Values datatype: ");
            aux.dataType+=userInputString();
            aux.dataType+=">";
            println("Nombre del dato: ");
            aux.dataName = userInputString();
            aux.totalDeclaration=
                aux.dataType +  " "  +
                aux.dataName + " = " +
                "new Hashmap<>();"
            ;
            clase.addImport("import java.util."+aux.dataType);
            complexDataType = true;
        }
        if(aux.dataType=="HashSet"  ){
            aux.dataType+="<";
            println("HashSet datatype: ");
            aux.dataType+=userInputString();
            aux.dataType+=">";
            println("Nombre del dato: ");
            aux.dataName = userInputString();
            aux.totalDeclaration =
                aux.dataType +  " "  +
                aux.dataName + " = " +
                "new HashSet<>();"
            ;
            clase.addImport("import java.util."+aux.dataType);
            complexDataType = true;
        }
        if(aux.dataType=="ArrayList"){
            aux.dataType+="<";
            println("Arraylist datatype: ");
            aux.dataType+=userInputString();
            aux.dataType+=">";
            println("Nombre del dato: ");
            aux.dataName = userInputString();
            aux.totalDeclaration =
                aux.dataType +  " "  +
                aux.dataName + " = " +
                "new ArrayList<>();"
            ;
            clase.addImport("import java.util."+aux.dataType);
            complexDataType = true;
        }
        if(aux.dataType=="LocalTime"||aux.dataType=="LocalDate"||aux.dataType=="LocalDateTime"){
            println("Nombre del dato: ");
            aux.dataName = userInputString();
            aux.totalDeclaration =
                aux.dataType +  " "  +
                aux.dataName + " = " +
                aux.dataType +
                ".now();"
            ;
            clase.addImport("import java.time."+aux.dataType);
            complexDataType = true;
        }

        if(!complexDataType && aux.dataType!="ready"){
            println("Nombre del dato: ");
            aux.dataName = userInputString();
            aux.totalDeclaration =
                aux.dataType +  " "  +
                aux.dataName + " = "
            ;
            if(aux.dataType=="String"/*||aux.dataType=="string"*/){
                //string comillas = int(string 34);
                //aux.totalDeclaration+=comillas;
                aux.totalDeclaration+="\"";
                println("Dato default(palabra): ");
                aux.totalDeclaration+=userInputString();
                //aux.totalDeclaration+=comillas;
                aux.totalDeclaration+="\"";
                aux.totalDeclaration+=";";
            }
            else if(
               aux.dataType == "int"     ||
               aux.dataType == "integer" ||
               aux.dataType == "Float"   ||
               aux.dataType == "float"
            ){
                println("Dato default(numero): ");
                aux.totalDeclaration+=userInputInt();
                aux.totalDeclaration+=";";
            }else{
                aux.totalDeclaration+="new ";
                aux.totalDeclaration+=aux.dataType;
                aux.totalDeclaration+="();";
            }
        }
        if(aux.dataType=="ready"){
            println("saliendo del loop");
            //println("sos re tonto.");
            loop = false;
        }else{
            clase.addVariable(aux);
        }


        clase.sayAllDeclarations();
    }
    //clases.push_back(clase);
    return clase;
}

int main(){
    while(true){
        println("1. Crear nueva clase");
        println("2. Fabricar clase(s)");
        println("3. Salir");
        switch(userInputInt()){
            case 1:
                clases.push_back(buildClase());
                break;
            case 2:
                for(int i=0;i<clases.size();i++){
                    writeFile(clases[i]);
                }
                break;
            case 3:
                return 0;
                break;
            default:
                println("Valor invalido boludito");
                break;
        }
    }


    return true;
}


//arreglar imports de estructuras complejas
//falta ; en inserts

