#include <iostream>
#include "./interfaces/individuo.h"

int main() {
    vector<int> g1;
    g1.push_back(1);
    Individuo x(g1,g1,g1);
    int evaluacion = x.evaluar();
    cout<<evaluacion<<endl;
    return 0;
}