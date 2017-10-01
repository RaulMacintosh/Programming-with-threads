#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

typedef std::vector<std::vector<float>> matriz;
typedef std::vector<float> vetor;

int m = 2048, n = 2048;
matriz A(m, vetor(n, 0));
matriz B(m, vetor(n, 0));

int lerA(string a){

	ifstream arq;
	arq.open(a.c_str());
	if(arq.is_open()){
		int d;
		arq >> d;  
		arq >> d;
		for(int i = 0; i < m; i++){
			for (int j = 0; j < n; ++j){
				arq >> A[i][j];
				
			}
		}
		arq.close();
	}
	return 0;
}

int lerB(string b){
	ifstream arq;
	arq.open(b.c_str());
	if(arq.is_open()){
		int d;
		arq >> d;  
		arq >> d;
		for(int i = 0; i < m; i++){
			for (int j = 0; j < n; ++j){
				arq >> B[i][j];
			}
		}
		arq.close();
	}
	return 0;
}

void product() {
	matriz C(m, vetor(n, 0));
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			for(int k = 0; k < n; k++){
				C[i][j] += A[i][k] * B[k][j];
			}
			cout << C[i][j] << " ";
		}
		cout <<"\n";
	}
}

void lerArgs(int argc, const char * argv[]){
	if(argc > 1)
		m = atoi(argv[1]);
	n = m;
	stringstream a,b;
	a <<"Matrizes/A" << m << "x" << m << ".txt";
	b <<"Matrizes/B" << m << "x" << m << ".txt";
	lerA(a.str());
	lerB(b.str());
}

void showTime(double tempoTotal){
	cout << "----------------------------"  << endl;
	cout << "Tempo Total: " << (tempoTotal*1000) << " ms"<< endl;
}

int main(int argc, const char * argv[]){
	
	auto t1 = std::chrono::high_resolution_clock::now();

	lerArgs(argc, argv);	//		./fatoracaoLU.cpp.o matrizA.txt vetorB.txt 3 3
	
	product();
	
	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> tempo = t2 - t1;
	double tempoTotal = tempo.count();
	
	showTime(tempoTotal);
	
	return 0;
}