#include <iostream>
#include <fstream>
#include <vector>
#include <string>


//Java Automatic Class Kreator


/*
------------------------------ TO DO ------------------------------
FIX:
  addMetodos
    anda pero lo toma como un tipo de variable asi q mal :(
    tipo los añade bien + los imports
    pero cuando hace los getters/setters/constructores lo toma como dato aunque este vacio :c
  conversion de int/float a string y no a char(std::to_string())
CHECK:
  corroborar que nada necesite std::
*/
/*
---------------------------- v4 idea ------------------------------
ARQUITECTURA GENERAL:
optimizar struct de datos a:
  struct var {
    dataType(T),
    name,
    default_value
  };
 
DATA TYPES & DATA STRUCTURES:
tener archivo externo con referencias de dataTypes/dataStructures y sus inicializadores e imports
-> sirve mas a la larga, archivo actualizable
-> mas comodo que un vector manual en el codigo + mas ordenado :D
-> modificable por consola (addDataType/addDataStructure) y manualmente (abrir archivo)
   -> si no esta en la lista se asume que es un objeto (sin import, inicializador new ())

crear switch para strings 
-> codigo mas legible y adaptable (ya hiciste este codigo 3 veces boludito!)

HERENCIA:
tener archivo externo que tenga otros objetos y sus constructores x parametros
-> asi super() se llena solo
-> se tiene los 2 
*/

using namespace std;

std::string extensionArchivo = ".java";
// ''
void println(std::string i){ std::cout<<i<<std::endl;  }

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
    std::vector<std::string> imports;
    std::vector<std::string> metodos;

    void addVariable(Variable    _var){
        this->variables.push_back(_var);
    }
    void addMetodos(std::string _metodo){
        this->metodos.push_back(_metodo);
    }

    void addVariable(std::string _dataType,std::string _dataName){    // No lo uso lol
        Variable var;
        var.dataName = _dataName;
        var.dataType = _dataType;
        this->variables.push_back(var);
    }

    void addImport  (std::string _import){
        int e=0;
        for(int i=0;i<imports.size();i++){
            if(imports[i]!=_import){ e++; }
        }
        if(e==imports.size()){
            this->imports.push_back(_import);
        }
    }
    void sayAllDeclarations(){
        for(int i=0;i<imports.size();i++){    std::cout<<imports[i]<<std::endl;   }

        for(int i=0;i<variables.size();i++){
            std::cout<<variables[i].totalDeclaration<<std::endl;
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

std::string userInputString(){
    std::string aux;
    std::cin>>aux;
    return aux;
}

int userInputInt(){
    int i;
    std::cin>>i;
    return i;
}

void writeFile(Clase clase){
    std::ofstream file(clase.nombre+extensionArchivo);

    /*ofstream file;
    file.open(clase.nombre+extensionArchivo);*/
    std::string sangria = "      " ;
//Imports
    for(int i=0;i<clase.imports.size();i++){
        file << clase.imports[i] << std::endl;
    }
    if(clase.imports.size()>0){ file << std::endl;   }
//
    file << "public class " + clase.nombre;
    if(clase.herencia!=""){ file << " extends " << clase.herencia; }
    file << " {" << std::endl << std::endl;
//atributos
    for(int i=0;i<clase.variables.size();i++){
        file << sangria <<"private " <<clase.variables[i].dataType << " " << clase.variables[i].dataName << ";" << std::endl;
    }
    file << std::endl;
//constructores
    //default
    file << sangria << "public " << clase.nombre << "() {"  << std::endl;
    if(clase.herencia!=""){ file << sangria      << sangria << "super();" << std::endl; }
    for(int i=0;i<clase.variables.size();i++){
        file << sangria << sangria << "this.";
        /*int aux = 0;
        for(int e=0;e<clase.variables[i].dataType.size();e++){
            if(clase.variables[i].dataType[e]     == clase.variables[i].totalDeclaration[e]){ aux++; }
            if(clase.variables[i].dataType.size() == aux){

            }
        }*/
        for(int e = clase.variables[i].dataType.size()+1; e<clase.variables[i].totalDeclaration.size(); e++){
            file << clase.variables[i].totalDeclaration[e];
        }
        file << std::endl;
    }
    file << sangria << "}" << std::endl << std::endl;
    //por parametros
    file << sangria << "public " << clase.nombre << "(";
    for(int i=0;i<clase.variables.size();i++){
        file << clase.variables[i].dataType << " " << clase.variables[i].dataName;
        if(i<clase.variables.size()-1){     file << ",";    }
    }
    file << ") {" <<std::endl;
    if(clase.herencia!=""){ file << sangria      << sangria << "super();" << std::endl; }
    for(int i=0;i<clase.variables.size();i++){
        file << sangria << sangria << "this." << clase.variables[i].dataName << " = " <<clase.variables[i].dataName << ";" << std::endl;
    }
    file << sangria << "}" << std::endl << std::endl;
//setters
    for(int i=0;i<clase.variables.size();i++){
        file << sangria;
        file << "public " << "void" << " set";
        //clase.variables[i].dataName;
        if(islower(clase.variables[i].dataName[0])){
            std::string aux=" ";
            aux = int(clase.variables[i].dataName[0])-32;
            file << aux;
        }
        for(int e=1;e<clase.variables[i].dataName.size();e++){
            file << clase.variables[i].dataName[e];
        }

        file << "("       << clase.variables[i].dataType << " i){"   ;
        file << " this."  << clase.variables[i].dataName << " = i; ";
        file << "}"       << std::endl;
    }
    file << std::endl;
//getters
    for(int i=0;i<clase.variables.size();i++){
        file << sangria;
        file << "public " << clase.variables[i].dataType << " get";
        // << clase.variables[i].dataName << "(){";
        if(islower(clase.variables[i].dataName[0])){
            std::string aux=" ";
            aux = int(clase.variables[i].dataName[0])-32;
            file << aux;
        }
        for(int e=1;e<clase.variables[i].dataName.size();e++){
            file << clase.variables[i].dataName[e];
        }
        file << "(){ return this." << clase.variables[i].dataName<< ";";
        file << " }" << std::endl;
    }
    file << std::endl;
//metodos
    for(int i=0;i<clase.metodos.size();i++){
        file << clase.metodos[i] << std::endl;
    }
    file << "}" << std::endl;
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

void addCrash(Clase&clase){
    clase.addMetodos("private static void crash(String errMsg){ System.out.println(errMsg); int e = 1/0;}");
}

Clase buildClase(){
    Clase clase;
    println("Nombre de la clase: ");
    clase.nombre = userInputString();
    println("Herencia? S/N");
    std::string temp = userInputString();
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
            clase.addImport("import java.util."+aux.dataType+";");
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
                "new HashMap<>();"
            ;
            complexDataType = true;
        }
        if(aux.dataType=="HashSet"  ){
            clase.addImport("import java.util."+aux.dataType+";");
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
            complexDataType = true;
        }
        if(aux.dataType=="ArrayList"){
            clase.addImport("import java.util."+aux.dataType+";");
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
            complexDataType = true;
        }
        if(aux.dataType=="LocalTime"||aux.dataType=="LocalDate"||aux.dataType=="LocalDateTime"){
            clase.addImport("import java.time."+aux.dataType+";");
            println("Nombre del dato: ");
            aux.dataName = userInputString();
            aux.totalDeclaration =
                aux.dataType +  " "  +
                aux.dataName + " = " +
                aux.dataType +
                ".now();"
            ;
            complexDataType = true;
        }
        if(aux.dataType=="addInput"){   addInputs(clase);     complexDataType=true;  }
        if(aux.dataType=="addPrints"){  addEasyPrints(clase); complexDataType=true;  }
        if(aux.dataType=="addCrash"){   addCrash(clase);      complexDataType=true;  }

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
               aux.dataType == "float"   ||
               aux.dataType == "Integer"
            ){
                println("Dato default(numero): ");
                aux.totalDeclaration += std::to_string(userInputInt());
                aux.totalDeclaration += ";";
            }else{
                aux.totalDeclaration+="new ";
                aux.totalDeclaration+=aux.dataType;
                aux.totalDeclaration+="();";
            }
        }

        if(aux.dataType=="ready"){
            println("saliendo del loop");
            //println("sos re tonto."); //cortesia de malitto
            loop = false;
        }else if(
            aux.dataType!="addInput" ||
            aux.dataType!="addPrints"||
            aux.dataType!="addCrash"
        ){
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
                clases.clear(); 
                //asi no reescribe archivos ya escritas
                //chequear si ese es el comando para vaciar vectores pq sino no anda :(
                break;
            case 3:
                return 0;
                break;
            default:
                println("Valor invalido boludito");
                break;
        }
    }
    return 0;
}
