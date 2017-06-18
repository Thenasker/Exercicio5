#ifndef VETOR_H
#define VETOR_H

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

using namespace std;

class Vetor
{

    private:

        int dimen;

    public:

        float * vals;

        Vetor();
        void setDim(int dim);
        void inserirValor(int pos, float val);
        float lerVal(int pos);
        void multEscalar(float escalar);
        int getDimen();
        string aString();
};

#endif // VETOR_H
