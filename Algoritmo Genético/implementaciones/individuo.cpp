#include "../interfaces/individuo.h"
#include <math.h>

int conseguirSuma(vector<int> s_x)
{
    int suma = 0; 
    for (int x : s_x)
        suma += x;
    return suma;
}

int evaluarCuadrados(int x_1, int x_2)
{
    int evaluacion = (x_1 - x_2);
    evaluacion = pow(evaluacion, 2);
    return evaluacion;
}

Individuo::Individuo(vector<int> s_1, vector<int> s_2, vector<int> s_3)
{
    s1 = s_1;
    s2 = s_2; 
    s3 = s_3;
};

int Individuo::evaluar()
{
    //f(s1, s2, s3) = (s1 - s2)^2 + (s1 - s3)^2 + (s2 - s3)^2.
    int calificacion = 0;
    int s_1 = conseguirSuma(s1);
    int s_2 = conseguirSuma(s2); 
    int s_3 = conseguirSuma(s3);
    calificacion = evaluarCuadrados(s_1, s_2) + evaluarCuadrados(s_1, s_3) + evaluarCuadrados(s_2, s_3);
    return calificacion;
}
