#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

string s=" <@> ";
string extensionArchivo=".txt";

int main(){
    std::cout << "the character \" is a quote"<<endl;

    string input,className;
    cout << "class-name"<<s;    cin>>input;
    className=input;

    string dataTypes[]={"int","string","float","bool","vector"};
    int dataTypesSize=sizeof(dataTypes)/sizeof(dataTypes[0]);
    vector<string>dataType;
    vector<string>dataName;
    vector<bool>  isVector;
    bool a=true;
    while(a){
        cout << "attribute-type"<<s;    cin>>input;
        if(input=="ready"){ a=false;}
    if(a){
        if(input=="int"){    dataType.push_back("int");     isVector.push_back(false); }
        if(input=="float"){  dataType.push_back("float");   isVector.push_back(false); }
        if(input=="string"){ dataType.push_back("String");  isVector.push_back(false); }
        if(input=="bool"){   dataType.push_back("boolean"); isVector.push_back(false); }
        if(input=="vector"){
            string aux;
            cout<<"Type of vector"<<s; cin>>input;
            if     (input=="string"){   aux="String";   }
            else if(input=="bool"){     aux="boolean";  }
            else{                       aux=input;      }
            string total = "ArrayList<"+aux+">";
            dataType.push_back(total);
            isVector.push_back(true);
        }

        cout << "attribute-name"<<s;    cin>>input;
        dataName.push_back(input);

        cout<<"Attributes: "<<endl;
        for(int i=0;i<dataType.size();i++){
            cout<<dataType[i]<<" "<<dataName[i]<<endl;
        }
        }
    }

    //Crear archivo
    string fileName=className+extensionArchivo;
    ofstream archivo(fileName);

    //Incluir librerías
    archivo<<""<<endl;
    archivo<<"import java.util.Scanner;"<<endl;
    archivo<<"import java.util.ArrayList;"<<endl;
    archivo<<endl;

    //Crear clase
    archivo<<"public class "+className+" {"<<endl;

    //crear atributos
    for(int i=0;i<dataType.size();i++){
            archivo<<"  private "+dataType[i]+" "+dataName[i]+";"<<endl;
    }

    archivo<<endl;

    //crear constructores
    archivo<<"public "+className+"(){"<<endl;
    for(int i=0;i<dataType.size();i++){
        if(isVector[i]==true){
            //
            /*string aux=dataName[i];
            if(aux[7]=="i"||aux[8]=="n"||aux[9]=="t"){
                archivo<<dataName[i]+" = new ArrayList<Integer>();"<<endl;
            }
            else if(aux[7]=="f"||aux[8]=="l"||aux[9]=="o"){
                archivo<<dataName[i]+" = new ArrayList<float>();"<<endl;
            }
            else if(aux[7]=="b"||aux[8]=="o"||aux[9]=="o"){
                archivo<<dataName[i]+" = new ArrayList<boolean>();"<<endl;
            }
            else if(aux[7]=="S"||aux[8]=="t"||aux[9]=="r"){
                archivo<<dataName[i]+" = new ArrayList<String>();"<<endl;
            }else{*/
                archivo<<dataName[i]+" = new ArrayList<>();"<<endl;
            /*}*/
        }
        else{
//            string comillas= int(string 34);
            if(dataType[i]=="String"){
                archivo<<"this."+dataName[i]+"=\"";
                cout<<"Default constructor, "<<dataType[i]<<" "<<dataName[i]<<" value: "; cin>>input;
                archivo<<input;
                archivo<<"\";"<<endl;
            }else{
            archivo<<"this."+dataName[i]+"=";
            cout<<"Default constructor, "<<dataType[i]<<" "<<dataName[i]<<" value: "; cin>>input;
            archivo<<input+";"<<endl;
            }

        }

    }
    archivo<<"}"<<endl;

    archivo<<"public "+className+"(";
    int aux = dataType.size();

    for(int i=0;i<dataType.size();i++){
            if(isVector[i]==true){
                aux--;
            }
            archivo<<dataType[i]+" "+dataName[i];
            if(i<aux-1){
                archivo<<",";
            }
    }
    archivo<<"){"<<endl;
    for(int i=0;i<dataType.size();i++){
            if(isVector[i]!=true){
                archivo<<" this."+dataName[i]+" = "+dataName[i]+";"<<endl;
            }else{
                archivo<<dataName[i]+" = new ArrayList<>();"<<endl;
            }
    }
    archivo<<"}"<<endl;

    //crear getters
    for(int i=0;i<dataType.size();i++){
        if(isVector[i]!=true){
            archivo<<"public "+dataType[i]+" get"+dataName[i]+"(){ ";
            archivo<<"return this."+dataName[i]+";}"<<endl;
        }else{

        }

    }
    archivo<<endl;

    //crear setters
    for(int i=0;i<dataType.size();i++){
        if(isVector[i]!=true){
            archivo<<"public void set"+dataName[i]+"("+dataType[i]+" "+dataName[i]+"){ this.";
            archivo<<dataName[i]+" = "+dataName[i]+"; }"<<endl;
        }else{

        }

    }
    archivo<<endl;
    archivo<<"}"<<endl;

    return 0;
}
