#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h> //system("CLS");
#define add(x) push_back(x)
using namespace std;

//{}

void sayDireccion(int direccion[4]){
    for(int i=0;i<4;i++){
        std::cout<<direccion[i];
        if(i<3){    std::cout<<".";  }
    }
    std::cout<<std::endl;
}

bool esPar(int n){
    if(n%2==0){
        return true;
    }
    return false;
}

void sayBinary8bits(bool octeto[8]){
    for(int i=0;i<8;i++){
        std::cout<<octeto[i];
        //if(i<7){    cout<<".";  }
    }
}

void sayBinary32Bits(bool direccionBinaria[32]){
    bool aux[8];

    for(int i=0;i<4;i++){
        for(int e=0;e<8;e++){
            aux[e]=direccionBinaria[i*8+e];
        }
        sayBinary8bits(aux);
        // cout<<".";
        if(i<3){    cout<<".";  }
    }cout<<endl;
}

void dirToBinary(int octeto,bool octetoBinario[8]){
    int n = octeto;
    bool aux[8];

    for(int i=0;i<8;i++){
        if(esPar(n)){
            aux[i]=false;
        }else{
            aux[i]=true;
            n--;
        }
        n/=2;
    }
    //Invierte el array
    int t=7;
    for(int i=0;i<8;i++){
        octetoBinario[i]=aux[t];
        t--;
    }
    /*
    for(int i=0;i<8;i++){
        cout<<octetoBinario[i]<<"-";
    }cout<<endl;*/
    //sayBinary8bits(octetoBinario);


}

void cls(){
    system("CLS");
}

void fillDireccion(int direccion[4]){
    int aux=0;

    for(int i=0;i<4;i++){
        cout<<"Octeto N "<<i<<": ";
        cin>>aux;

        if(aux>255 || aux<0){
            cout<<"Valor invalido"<<endl;
            i--;
        }else{
            direccion[i]=aux;
            sayDireccion(direccion);
        }
    }
}

void fillMascara(int &mascara){
    bool e = true;
    int aux=0;
    while(e){
        cout<<"Mascara: /";
        cin>>aux;
        if(aux>31 || aux<0){
            cout<<"Valor invalido"<<endl;
        }else{
            e=false;
            mascara=aux;
        }
    }
}

void fillDireccionBinaria(int direccion[4],bool direccionBinaria[32]){
    bool temp8bits[8];
    for(int i=0;i<4;i++){
        dirToBinary(direccion[i],temp8bits);
        for(int e=0;e<8;e++){
            direccionBinaria[i*8+e]=temp8bits[e];
        }
    }
}

void fillMascaraBinaria(int mascara,bool mascaraBinaria[32]){
    for(int i=0;i<32;i++){
        if(i>=mascara){
            mascaraBinaria[i]=0;
        }else{
            mascaraBinaria[i]=1;
        }
    }
}

int bitsToDecimal(int bits){
    int out=0;
    if(bits==0){    return 0;   }else{
        out=2;
    }
    for(int i=0;i<bits-1;i++){
        out*=2;
    }
    return out;
}

int hostsDisponiblesTotal(bool mascaraBinaria[32]){
    int ceros=0;
    for(int i=0;i<32;i++){
        if(!mascaraBinaria[i]){
            ceros++;
        }
    }
    return bitsToDecimal(ceros)-1;
}

void sayData(int direccion[4],bool direccionBinaria[32],int submascara,bool submascaraBinaria[32]){
    cout<<"Red -------> ";
    for(int i=0;i<4;i++){
        cout<<direccion[i];
        if(i<3){    cout<<".";  }
    }
    cout<<"   /"<<submascara<<endl;
    cout<<"Direccion -> ";
    sayBinary32Bits(direccionBinaria);
    cout<<"Mascara ---> ";
    sayBinary32Bits(submascaraBinaria);

    cout<<"Hosts disponibles: "<<hostsDisponiblesTotal(submascaraBinaria)<<endl;

}

struct redData{
    std::string nombre;
    int n_hosts;
    int n_hosts_total;
};

int hostsGiven(int num){
    int out=4;
    while(num>out){
        out*=2;
    }
    return out;
}

void addRed(std::vector<redData> &redes){
    redData RD;
    cout<<"Nombre red: ";
    cin>>RD.nombre;
    cout<<"Cantidad hosts: ";
    cin>>RD.n_hosts;
    RD.n_hosts_total=hostsGiven(RD.n_hosts);
    cout<<"Hosts otorgados: "<<RD.n_hosts_total<<endl;
    redes.add(RD);
}

void sayAllRed(std::vector<redData> redes){
    for(int i=0;i<redes.size();i++){
        cout<<"Nombre:"<<redes[i].nombre<<" | Hosts:"<<redes[i].n_hosts<<" | Otorgados:"<<redes[i].n_hosts_total<<endl;
    }
}

int menu(){
    int userInput;
    cout<<endl;
    cout<<"1 - Anadir red."<<endl;
    cout<<"2 - Redes actuales"<<endl;
    cout<<"3 - Direccion red"<<endl;
    cout<<"6 - Salir."<<endl;
    cout<<"7 - CLS"<<endl;
    cout<<"@";
    cin>>userInput;
    return userInput;
}

int main(){
    //32 bits 8-8-8-8
    bool direccionBinaria[32];
    bool submascaraBinaria[32];
    int  submascara=0;
    int  direccion[]={0,0,0,0};
    std::vector<redData> redes;

    fillDireccion(direccion);
    fillMascara  (submascara);
    fillDireccionBinaria(direccion,direccionBinaria);
    fillMascaraBinaria(submascara,submascaraBinaria);

    cls();

    bool men=true;
    while(men){
        switch(menu()){
            case 1: addRed(redes); break;
            case 2: sayAllRed(redes);     break;
            case 3: sayData(direccion,direccionBinaria,submascara,submascaraBinaria); break;
            case 6: men=false; break;
            case 7: cls(); break;
            default: cout<<"invalid option"<<endl; break;
        }
    }


    return 0;
}
