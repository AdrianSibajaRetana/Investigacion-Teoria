#include "../interfaces/individuo.h"
#include <math.h>

long long conseguirSuma(vector<int> s_x)
{
    long long suma = 0; 
    for (int x : s_x)
        suma += x;
    return suma;
}

long long evaluarCuadrados(long long x_1, long long x_2)
{
    long long evaluacion = (x_1 - x_2);
    evaluacion = pow(evaluacion, 2);
    return evaluacion;
}

Individuo::Individuo(vector<int> s_1, vector<int> s_2, vector<int> s_3)
{
    s1 = s_1;
    s2 = s_2; 
    s3 = s_3;
    puntaje = 0;
};

void Individuo::evaluar()
{
    long long s_1 = conseguirSuma(s1);
    long long s_2 = conseguirSuma(s2);
    long long s_3 = conseguirSuma(s3);
    puntaje = evaluarCuadrados(s_1, s_2) + evaluarCuadrados(s_1, s_3) + evaluarCuadrados(s_2, s_3);
}