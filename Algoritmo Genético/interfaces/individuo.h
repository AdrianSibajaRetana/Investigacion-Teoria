#ifndef INDIVIDUO_H
#define INDIVIDUO_H

#include <vector>
using namespace std;

class Individuo
{
    private: 
    	vector<int> s1;
		vector<int> s2;
		vector<int> s3;
		
	
	public:
		Individuo(vector<int> s_1, vector<int> s_2, vector<int> s_3);
		void evaluar();
		void imprimir();
		long long puntaje;

};

#endif 