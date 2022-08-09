#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

string extensionArchivo = ".txt";
// ''



struct Variable {
    string dataType;
    string dataName;
    string totalDeclaration="";
};

struct DataTypesInfo{
    std::string dataType;
    std::string initializer;
    std::string imports;
};

class Clase{
//private:
public:
    std::vector<Variable> variables;
    std::string nombre;
    std::string herencia = "";
    std::vector<string> imports;
//public:
    void addVariable(Variable    _var){
        this->variables.push_back(_var);
    }
    void addVariable(string _dataType,string _dataName){
        Variable var;
        var.dataName = _dataName;
        var.dataType = _dataType;
        this->variables.push_back(var);
    }
    void setHerencia(string _herencia){
        this->herencia = _herencia;
    }
    void setNombre  (string _nombre){
        this->nombre = _nombre;
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

};
std::vector<Clase> clases;

std::vector<DataTypesInfo> inicializadores(){

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
    //Imports
    //public class <name> {
    //atributos
    //metodos
}

/*std::string checkIsInVector(string in){
    std::vector<DataTypesInfo> aux = inicializadores();
    for(int i=0;i<aux.size();i++){
        if(int == aux[i].dataType){
            return string
        }
    }
}*/

void println(string i){ cout<<i<<endl;  }

Clase buildClase(){
    Clase clase;
    println("Nombre de la clase: ");
    clase.nombre = userInputString();
    println("Herencia? S/N");
    string temp = userInputString();
    if(temp=="S"||temp=="s"||temp=="Y"||temp=="y"){
        println("Inserte nombre de la herencia: ");
        clase.herencia = userInputString();
    }

    println("Atributos,esciba ready para finalizar, toque cualquier tecla ");

    while(userInputString()!="ready"){
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
            clase.addImport("import java.util."+aux.dataName);
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
            clase.addImport("import java.util."+aux.dataName);
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
            clase.addImport("import java.util."+aux.dataName);
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
            clase.addImport("import java.time."+aux.dataName);
            complexDataType = true;
        }

        if(!complexDataType){
            println("Nombre del dato: ");
            aux.dataName = userInputString();
            aux.totalDeclaration =
                aux.dataType +  " "  +
                aux.dataName + " = "
            ;
            if(aux.dataType=="String"){
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



        cout<<aux.totalDeclaration<<endl;
        clase.addVariable(aux);
    }

}

bool menu(){
    println("1. Crear nueva clase");
    println("2. Fabricar clase(s)");
    println("3. Salir");
    switch(userInputInt()){
        case 1: buildClase(); break;
        case 2:  break;
        case 3: return false; break;
        default: println("Valor invalido boludito"); break;
    }
    return true;
}

int main(){
  //Falta lo que escribe el archivo!!!
    while(menu()){}

    return 0;
}
