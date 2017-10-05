#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

using namespace std::chrono;
using namespace std;

typedef std::vector<std::vector<float>> matriz;
typedef std::vector<float> vetor;

int m = 2048, n = 2048, threads_number=1;
matriz A(m, vetor(n, 0));
matriz B(m, vetor(n, 0));
matriz C(m, vetor(n, 0));

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

void partial_product(int i, int f) {
	for(; i < f; i++){
		for(int j = 0; j < m; j++){
			for(int k = 0; k < m; k++){
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}


void product() {

	std::thread threads[threads_number];

	int factor = m/threads_number;

	for(int i = 0; i < m; i+=factor){
		threads[i/factor] = std::thread(partial_product, i, i+factor);
	}
	for(int i = 0; i < threads_number; i++){
		threads[i].join();
	}

}


void writeResultMatrix(){
	ofstream output;
	string fileName = "Results/C" + to_string(m) + "x" + to_string(m) + ".txt";
	output.open (fileName);

	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			output << C[i][j] << " ";
		}
		output << "\n";
	}

	output.close();
}

void lerArgs(int argc, const char * argv[]){
	if(argc > 1)
		m = atoi(argv[1]);
	if(argc > 2)
		threads_number = atoi(argv[2]);
	n = m;
	stringstream a,b;
	a <<"Matrizes/A" << m << "x" << m << ".txt";
	b <<"Matrizes/B" << m << "x" << m << ".txt";
	lerA(a.str());
	lerB(b.str());
}

void showTime(double tempoTotal){
	ofstream output;
	output.open ("Times.txt", fstream::app);
	string content = "C" + to_string(m) + "x" + to_string(m) + ": " + to_string(tempoTotal) + "\n";
	output << content;
}

int main(int argc, const char * argv[]){
	
	steady_clock::time_point t1 = steady_clock::now();

	lerArgs(argc, argv);
	
	product();
	
	writeResultMatrix();

	steady_clock::time_point t2 = steady_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	double tempoTotal = time_span.count();

	showTime(tempoTotal);
	
	return 0;
}