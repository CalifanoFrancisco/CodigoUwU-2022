#include <iostream>
#include <Class.h>
using namespace std;

vector<string> varTypes(){
    vector<string> aux;
    aux.push_back("Integer");
    aux.push_back("int");
    aux.push_back("Float");
    aux.push_back("ArrayList");
    aux.push_back("HashMap");
    aux.push_back("LocalDate");
    aux.push_back("LocalTime");
    aux.push_back("LocalDateTime");
    aux.push_back("boolean");
    aux.push_back("String");

    return aux;
}

int main()
{
    cout << "Hello world!" << endl;
    cout<<"Crear nueva clase"<<endl;
    Class clase = Class();
    vector<string> aaa = varTypes();
    clase.setVarTypes(aaa);
    clase.addVariable();
    return 0;
}
