#include "individuo.h"
#include <math.h>
#include <random>
#include <iostream>
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


Individuo::Individuo(vector<int> s_1, vector<int> s_2, vector<int> s_3, vector<int> numeros_usados)
{
    s1 = s_1;
    s2 = s_2; 
    s3 = s_3;
    cadenaGenetica = numeros_usados;
    puntaje = 0;
};

Individuo::Individuo(vector<int> numeros_usados, vector<int> numeros)
{
    cadenaGenetica = numeros_usados;
    puntaje = 0;
    construirAPartirDeCadenaGenetica(numeros);
};

void Individuo::evaluar()
{
    long long s_1 = conseguirSuma(s1);
    long long s_2 = conseguirSuma(s2);
    long long s_3 = conseguirSuma(s3);
    puntaje = evaluarCuadrados(s_1, s_2) + evaluarCuadrados(s_1, s_3) + evaluarCuadrados(s_2, s_3);
}

void Individuo::mutar(double probabilidadDeMutar)
{
    for(int i = 1; i <= 3; i++)
        mutarVector(i, probabilidadDeMutar);
}

void Individuo::mutarVector(int vectorActual, double probabilidadDeMutar)
{
    int tamañoVectorAMutar;
    int tamañoVectorAMutar2;
    switch(vectorActual) {
            case 1:
                tamañoVectorAMutar = s1.size();
                tamañoVectorAMutar2 = s2.size();
                break;
            case 2:
                tamañoVectorAMutar = s2.size();
                tamañoVectorAMutar2 = s3.size();
                break;
            case 3:
                tamañoVectorAMutar = s3.size();
                tamañoVectorAMutar2 = s1.size();
                break;            
        }
    for(int i = 0; i < tamañoVectorAMutar; ++i)
    {
        auto probabilidad = ((double) rand() / (RAND_MAX));
        if(probabilidad <= probabilidadDeMutar)
        {
            int valorTemporal;
            int valorTemporal2; 
            int indiceAleatorio = rand() % tamañoVectorAMutar2;
            if(vectorActual == 1)
            {
                valorTemporal = s1[i];
                valorTemporal2 = s2[indiceAleatorio];
                s1[i] = valorTemporal2;
                s2[indiceAleatorio] = valorTemporal;                          
            }
            else if(vectorActual == 2)
            {
                valorTemporal = s2[i];
                valorTemporal2 = s3[indiceAleatorio];
                s2[i] = valorTemporal2;
                s3[indiceAleatorio] = valorTemporal;
            }
            else
            {
                valorTemporal = s3[i];                
                valorTemporal2 = s1[indiceAleatorio];
                s3[i] = valorTemporal2;
                s1[indiceAleatorio] = valorTemporal;
            }
        }
    }
}

void Individuo::construirAPartirDeCadenaGenetica(vector<int> numeros)
{
    int indiceActual = 0;
    int numeroAAñadir;
    for (int gen : cadenaGenetica)
    {   
        numeroAAñadir = numeros[indiceActual++];
        switch(gen) {
            case 1:
                s1.push_back(numeroAAñadir);
                break;
            case 2:
                s2.push_back(numeroAAñadir);
                break;
            case 3:
                s3.push_back(numeroAAñadir);
                break;            
        }
    }        
}