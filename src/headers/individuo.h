#pragma once

#include <vector>
using namespace std;

class Individuo
{
    private:
		// Las bolsas son representadas por vectores de números enteros
		vector<int> s1;
		vector<int> s2;
		vector<int> s3;
		// Se muta el vector indicado por "vectorActual" con 
		// la probabilidad determinada por "probabilidadDeMutar"
		void mutarVector(int vectorActual, double probabilidadDeMutar);
		// Se generan los valores de los vectores a partir de una
		// cadena genética recibida      
		void construirAPartirDeCadenaGenetica(vector<int> numeros);
	
	public:
		// puntaje otorgado por la fórmula dada.
		// determina la aptitud del individuo        
		long long puntaje;
		// este vector va 1 a 1 con los números leídos del .txt e indica
		// qué numero fue a qué bolsa. Esto es para evitar la duplicación de
		// números en las etapas de cruce o mutación    
		vector<int> cadenaGenetica;
		// Constructor inicial.    
		Individuo(vector<int> s_1, vector<int> s_2, vector<int> s_3, vector<int> numeros_usados);        
		// Constructor a partir de una cadena genética
		Individuo(vector<int> cadena_genetica, vector<int> numeros);
		// Se establece un valor a la propiedad "puntaje" a partir
		// de la fórmula "f(s1, s2, s3) = (s1 - s2)^2 + (s1 - s3)^2 + (s2 - s3)^2."
		void evaluar();
		// Llama al método construirAPartirDeCadenaGenetica para cada vector
		void mutar(double probabilidadDeMutar);

};
