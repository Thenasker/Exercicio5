/*
*   Exercicio 1.
*
*
*   Implemente o processo de ortogonalzação de GRAM-SCHIMDT. https://pt.wikipedia.org/wiki/Processo_de_Gram-Schmidt
*
*
*   Exemplos: https://youtu.be/6eTCfirtKr8?t=9m50s
*   (110)(011)(101)  -  (110)(-1/2 1/2 1)(2/3 -2/3 2/3)  -  (1/sqrt(2) 1/sqrt(2) 0)(-sqrt(1/6) sqrt(1/6) sqrt(2/3))(sqrt(3)/3 -sqrt(3)/3 sqrt(3)/3)
*
*/


/////////////////////////////INCLUDES
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <windows.h>
#include <fstream>
#include <ctime>
#include <sstream>
#include <dirent.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>
#include <bitset>
#include "Vetor.h"
/////////////////////////////INCLUDES

/////////////////////////////DEFINES
//Definiçao do string do menu
#define menu "\n1-- Ortogonalizar vetores\n\n2-- Achar base ortonormal\n\n3-- Projecao de um vetor sobre um subespaco de V\n\n0--Sair\n\n"
//Definiçao do tamaño do nome dos arquivos a salver e do formato deles
#define CHAR_VACIO '_'
#define DIMMAX 10
#define NUMMAX 10
/////////////////////////////DEFINES

using namespace std;


//Funçao que mostra o menu de opçoes inicial
int mostrarMenu(){

    int opcao=-1;

    //Enquanto o usuario nao escreva uma opçao valida o menu vai se mostrar uma e outra vez.
    while(opcao<0 || opcao>7){
        system("cls");
        //Usamos a variavel definida 'menu'
        cout << menu << endl;
        cin >> opcao;
        if(opcao<0 || opcao>7){
            cout << "Inserir uma opcao valida (0-7)" << endl;
            Sleep(2000);
        }
    }
    return opcao;
}

//funçao para perguntar ao usuario se ele quer finalizar o apicativo o mostrar o menu inicial outra vez
bool finalizar(){

    char fim = CHAR_VACIO;

    //Se pergunta ao usuario se que sair e devolve um valor booleano para a funçao main
    while(fim!='S' && fim!='s' && fim!='N' && fim!='n'){
        cout << "\n\n\nDeseja finalizar o programa? (S/N)" << endl;
        cin >> fim;
    }

    if(fim=='S' || fim == 's'){
        return true;
    }else{
        return false;
    }

}

//devolve o produto escalar de dois vetores passados como parametro
float escalar(Vetor v, Vetor u){

    float result =0;

    for(int i=0; i<v.getDimen(); i++){
        result+=v.lerVal(i)*u.lerVal(i);
    }

    return result;

}

//devolve um vetor que é substraçao dos vetores passados como parametros (v-u)
Vetor subs(Vetor v, Vetor u){

    Vetor s;

    s.setDim(v.getDimen());

    for(int i=0; i<v.getDimen() ; i++){
        s.inserirValor(i,v.lerVal(i) - u.lerVal(i));
    }

    return s;
}

//devolve um vetor que é soma dos vetores passados como parametros
Vetor soma(Vetor v, Vetor u){

    Vetor s;

    s.setDim(v.getDimen());

    for(int i=0; i<v.getDimen() ; i++){
        s.inserirValor(i,v.lerVal(i) + u.lerVal(i));
    }

    return s;
}

//funçao usada para calcular a parte mais complexa do processo de gram-schmidt que receve o vetor vn e o vetor vn-i ja ortogonalizado e devolve a parte que tem que se substrair
Vetor getAlfa(Vetor vetorj, Vetor v){

    Vetor aux;
    aux.setDim(vetorj.getDimen());

    for(int i=0; i< aux.getDimen() ; i++){
        aux.inserirValor(i, vetorj.lerVal(i));
    }

    aux.multEscalar(escalar(v,aux)/escalar(aux,aux));

    return aux;
}

//funçao para ortogonalizar. os loops percorrem cada vetor da lista e substrai n-1 vezes o resultado de getAlfa() com os vetores anteriores
void ortogonalizar(vector<Vetor> &vetores, int num){

    Vetor aux;
    aux.setDim(vetores.at(0).getDimen());

    system("cls");

    for(int i=0 ; i<num ; i++){

        aux = vetores.at(i);

        for(int j=i-1 ; j>=0 ; j--){

            vetores.at(i) = subs(vetores.at(i),getAlfa(vetores.at(j),aux));

        }
    }
}

//Funçao que divide os vetores por seu modulo para obter a base ortonormal que formam
void ortonormalizar(vector<Vetor> &vetores, int num){

    for(int i=0 ; i<num ; i++){
        vetores.at(i).setModulo();
        for(int j=0 ; j<vetores.at(i).getDimen(); j++){
            vetores.at(i).inserirValor(j,vetores.at(i).lerVal(j)/vetores.at(i).getModulo());
        }
    }

}

//Antes de ortogonalizar temos que comprovar se esses vetores sao linealmente independientes
//para fazer isso pegamos cada coordenada de cada vetor e comprovamos se existe uma razao igual para as n componentes de cada par de vetores
bool comprobarIndependencia(vector<Vetor> &vetores, int num){

    bool indep = true;
    int cont=0;
    float r=0;

    for(int i=0 ; i<num ; i++){
        for(int j=0 ; j<num ; j++){
            if(i!=j){
                r = vetores.at(i).lerVal(0)/vetores.at(j).lerVal(0);
                for(int k=0 ; k<vetores.at(i).getDimen() ; k++){

                    if(vetores.at(i).lerVal(k)/vetores.at(j).lerVal(k) == r) cont++;
                }
                if(cont == vetores.at(i).getDimen()) indep = false;
                cont = 0;
            }
        }
    }

    return indep;
}

// criamos o vetor projetado na base B seguindo o processo: v = <v1,e1>e1 + <v2,e2>e2 + <v3,e3>e3 + ... + <vn,en>en
void projecao(vector<Vetor> vetores, Vetor &v, int num){

    Vetor aux;
    aux.setDim(v.getDimen());

    for(int i=0 ; i<num ; i++){
        vetores.at(i).multEscalar(escalar(vetores.at(i),v));
        aux = soma(aux,vetores.at(i));
    }

    v = aux;

}

//Funçoes que gerenciam as funcionalidades do programa
bool opcao1(){

    int dim=0;
    int numVet=0;
    int val=0;
    vector<Vetor> vetores;

    system("cls");

    while(dim<2 || dim>DIMMAX){ //DIM MAXIMA MODIFICAVEL

        cout << "Inserir dimensao do espaco vetorial (MAX " << DIMMAX << ")." << endl;
        cin >> dim;

    }

    while(numVet<2 || numVet>NUMMAX){ //NUM MAXIMO MODIFICAVEL

        cout << "Inserir quantidade de vetores (MAX " << DIMMAX << ")." << endl;
        cin >> numVet;

    }

    system("cls");

    for(int i=0; i< numVet; i++){

        Vetor aux;
        aux.setDim(dim);
        for(int j=0; j<dim; j++){
            cout << "Vetor " << i+1 << " coordenada " << j+1 << endl;
            cin >> val;
            aux.inserirValor(j,val);
        }

        vetores.push_back(aux);
    }

    if(comprobarIndependencia(vetores, numVet)){

        ortogonalizar(vetores, numVet);

        cout << endl;
        for(int i=0 ; i<numVet ; i++){
            cout << "v" << i+1 << "' = " << vetores.at(i).aString() << endl;
        }

    }else{
        system("cls");
        cout << "Os vetores nao sao linealmente independientes. Tente de novo com outros vetores." << endl;
        system("pause");
        return false;
    }

    //devolvemos o valor que vamos obter da funçao finalizar()
    return finalizar();
}

bool opcao2(){

    int dim=0;
    int numVet=0;
    int val=0;
    vector<Vetor> vetores;

    system("cls");

    while(dim<2 || dim>DIMMAX){ //DIM MAXIMA MODIFICAVEL

        cout << "Inserir dimensao do espaco vetorial (MAX " << DIMMAX << ")." << endl;
        cin >> dim;

    }

    while(numVet<2 || numVet>NUMMAX){ //NUM MAXIMO MODIFICAVEL

        cout << "Inserir quantidade de vetores (MAX " << DIMMAX << ")." << endl;
        cin >> numVet;

    }

    system("cls");

    for(int i=0; i< numVet; i++){

        Vetor aux;
        aux.setDim(dim);
        for(int j=0; j<dim; j++){
            cout << "Vetor " << i+1 << " coordenada " << j+1 << endl;
            cin >> val;
            aux.inserirValor(j,val);
        }

        vetores.push_back(aux);
    }


    if(comprobarIndependencia(vetores, numVet)){

        ortogonalizar(vetores, numVet);

        ortonormalizar(vetores, numVet);

        cout << "\nB = {";
        for(int i=0 ; i<numVet ; i++){
            cout << vetores.at(i).aString();
            if(i != numVet-1)  cout << " , ";
        }
        cout << "}" << endl;

    }else{
        system("cls");
        cout << "Os vetores nao sao linealmente independientes. Tente de novo com outros vetores." << endl;
        system("pause");
        return false;
    }

    //devolvemos o valor que vamos obter da funçao finalizar()
    return finalizar();
}

bool opcao3(){

    int dim=0;
    int numVet=0;
    int val=0;
    vector<Vetor> vetores;
    Vetor v;
    stringstream ss;

    system("cls");

    while(dim<2 || dim>DIMMAX){ //DIM MAXIMA MODIFICAVEL

        cout << "Inserir dimensao do espaco vetorial (MAX " << DIMMAX << ")." << endl;
        cin >> dim;

    }

    v.setDim(dim);

    while(numVet<2 || numVet>NUMMAX){ //NUM MAXIMO MODIFICAVEL

        cout << "Inserir quantidade de vetores que vao formar a Base ortonormal (MAX " << DIMMAX << ")." << endl;
        cin >> numVet;

    }

    system("cls");

    for(int i=0; i< numVet; i++){

        Vetor aux;
        aux.setDim(dim);
        for(int j=0; j<dim; j++){
            cout << "Vetor " << i+1 << " coordenada " << j+1 << endl;
            cin >> val;
            aux.inserirValor(j,val);
        }

        vetores.push_back(aux);
    }


    if(comprobarIndependencia(vetores, numVet)){

        ortogonalizar(vetores, numVet);

        ortonormalizar(vetores, numVet);

        ss << "\n Vetor projetado na base B = {";
        for(int i=0 ; i<numVet ; i++){
            ss << vetores.at(i).aString();
            if(i != numVet-1)  ss << " , ";
        }

        for(int j=0; j<dim; j++){
            cout << "Vetor a projetar. Coordenada " << j+1 << endl;
            cin >> val;
            v.inserirValor(j,val);
        }

        projecao(vetores, v, numVet);

        cout << ss.str() << "}: " << v.aString() <<endl;

    }else{
        system("cls");
        cout << "Os vetores nao sao linealmente independientes. Tente de novo com outros vetores." << endl;
        system("pause");
        return false;
    }

    //devolvemos o valor que vamos obter da funçao finalizar()
    return finalizar();
}

//Funçao main
int main(){

    bool finalizar = false;

    //Mostramos a introduçao
    cout << "Linguagem de programacao" << endl;
    cout << "AV2. Questao 5. Ortogonalizacao." << endl;
    cout << "Pablo Rufat Munoz" << endl;
    cout << "Marcos Marques" << endl;
    cout << "2017/1\n\n" << endl;
    system("pause");

    //Mientras a funçao finalizar() nao devolva true, vamos chamar a funçao que mostra o menu.
    while(!finalizar){
        switch(mostrarMenu()){
            case(0):
                finalizar = true;
                break;
            case(1):
                finalizar = opcao1();
                break;
            case(2):
                finalizar = opcao2();
                break;
            case(3):
                finalizar = opcao3();
                break;
            default:
                finalizar = true;
                break;
        };
    }
    return 0;
}
