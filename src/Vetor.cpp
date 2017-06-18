
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


using namespace std;

Vetor::Vetor(){}

void Vetor::setDim(int dim)
{
    dimen = dim;
    vals = new float[dim];
}

void Vetor::inserirValor(int pos, float val){
    vals[pos] = val;
}

float Vetor::lerVal(int pos){

    return vals[pos];
}


void Vetor::multEscalar(float escalar){
    for(int i=0; i<dimen ; i++){
        vals[i] = vals[i] * escalar;
    }
}

int Vetor::getDimen(){
    return dimen;
}

string Vetor::aString(){

    string result;
    stringstream ss;

    result.insert(0,"(");

    for(int i=0 ; i<dimen ; i++){
        ss << vals[i];
        ss << ", ";
    }
    ss << ")";
    result.append(ss.str());

    return result;
}
