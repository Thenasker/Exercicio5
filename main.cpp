/*
*   Exercicio 1.
*
*   Crie uma paleta de cores onde cada pixel é colorido pelo valor de x e y. A saida do
*   programa deve ser uma paleta muito proxima a paleta descrita abaixo:
*
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
#define menu "\n1-- Ortogonalizar vetores\n\n2--\n\n3--\n\n4--\n\n0--Sair\n\n"//Definiçao do tamaño do nome dos arquivos a salver e do formato deles
#define CHAR_VACIO '_'
#define DIMMAX 5
#define NUMMAX 5
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

float escalar(Vetor v, Vetor u){

    float result =0;

    for(int i=0; i<v.getDimen(); i++){
        result+=v.lerVal(i)*u.lerVal(i);
    }

    return result;

}

Vetor subs(Vetor v, Vetor u){

    Vetor s;

    s.setDim(v.getDimen());

    for(int i=0; i<v.getDimen() ; i++){
        s.inserirValor(i,v.lerVal(i) - u.lerVal(i));
    }

    return s;
}

Vetor getAlfa(Vetor *vetores, Vetor v, int j){

    Vetor aux;

    aux = vetores[j];

    aux.multEscalar(escalar(v,aux)/escalar(aux,aux));

    return aux;
}

void ortogonalizar(Vetor *vetores, int num){

    Vetor aux;
    aux.setDim(vetores[0].getDimen());

    system("cls");

    for(int i=1 ; i<num ; i++){

        aux = vetores[i];

        for(int j=i-1 ; j>=0 ; j--){
            vetores[i] = subs(vetores[i],getAlfa(vetores,aux,j));
        }
        cout << vetores[i].aString() << endl;
    }

/*

    for(int k=0; k< numVet; k++){

        cout << "(";
        for(int l=0; l< vetores[k].getDimen(); l++){
            cout << vetores[k].lerVal(l) << ",";
        }

        cout << ")" << endl;
    }*/
    system("pause");

}

bool opcao1(){

    //TODO: LER DIMEN
    //TODO: CRIAR ARRAY Vetor
    //TODO: ENCHER ARRAY
    //TODO: ORTO

    int dim=0;
    int numVet=0;
    int val=0;
    Vetor *vetores;

    system("cls");

    while(dim<2 || dim>DIMMAX){ //DIM MAXIMA MODIFICAVEL

        cout << "Inserir dimensao do espaco vetorial (MAX " << DIMMAX << ")." << endl;
        cin >> dim;

    }

    while(numVet<2 || numVet>NUMMAX){ //NUM MAXIMO MODIFICAVEL

        cout << "Inserir quantidade de vetores (MAX " << DIMMAX << ")." << endl;
        cin >> numVet;

    }

    vetores = new Vetor[numVet];
    system("cls");

    for(int i=0; i< numVet; i++){
        vetores[i].setDim(dim);

        for(int j=0; j<dim; j++){
            cout << "Vetor " << i+1 << " coordenada " << j+1 << endl;
            cin >> val;
            vetores[i].inserirValor(j,val);
        }
    }

    ortogonalizar(vetores, numVet);

    /*for(int i=0; i< numVet; i++){

        cout << "(";
        for(int j=0; j< dim; j++){
            cout << vetores[i].lerVal(j) << ",";
        }

        cout << ")" << endl;
    }*/

    system("pause");
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
                //finalizar = opcao2();
                break;
            case(3):
                //finalizar = opcao3();
                break;
            case(4):
                //finalizar = opcao4();
                break;
            case(5):
                //finalizar = opcao5();
                break;
            default:
                //finalizar = true;
                break;
        };
    }
    return 0;
}
