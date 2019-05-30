// GCC 6.2.0

#include <bits/stdc++.h>
using namespace std;


double E;
double f1(double x);
double f2(double x);
double f3(double x);
double f4(double x);
double trapezoidal(int step, double a, double b, double(*f)(double x));
double simpson(int step, double a, double b, double(*f)(double x));
double romberg(double EPS,double a, double b, double(*f)(double x));

void run() {
	// sin(x) 0 , 4
	int n = 10;
	cout << trapezoidal(n,0,4,f1) << endl;
	cout << simpson(n,0,4,f1) << endl;
}

void getE() {
	int n = 20;
	double fac = 1;
	E = 1;	
	for(int i = 1;i <= n;i++) {
		fac *= i;
		E += 1.0/fac;
	}
}

int main(){
	getE();
	// cout << fixed << E << endl;
	run();
	return 0;
}

double f1(double x) {
	return sin(x);
}
double f2(double x) {
	return sin(x) / x;
}
double f3(double x) {
	return pow(E,x) / (5 + x * x);
}
double f4(double x) {
	return 4 / (1 + x * x);
}
double trapezoidal(int step, double a, double b, double(*f)(double x)) {
	double h = (b - a) / step, res = 0;
	res = f(a) + f(b);
	double x = a;
	for(int i = 1;i <= step - 1;i ++) {
		x += h;
		res += 2 * f(x);  
	}	
	return res / 2 * h;
}

double simpson(int step, double a, double b, double(*f)(double x)) {
	double h = (b - a) / step, res = 0;
	res = f(a) + f(b);
	double x = a - 0.5 * h;
	for(int i = 1;i <= step;i++) {
		x += h;
		res += 4 * f(x);
	}
	x = a;
	for(int i = 1;i <= step - 1;i++) {
		x += h;
		res += 2 * f(x);
	}
	return res / 6 * h;
}

double romberg(double EPS, double a,double b,double(*f)(double x)) {
	vector<vector<double>> T;
	T.push_back(vector<double>());
	double temp = 0, h;
	temp = (b - a) / 2 * (f(a) + f(b));
	T[0].push_back(temp);
	int k = 0;
	do {
		k++;
		T.push_back(vector<double>());
		h = (b - a) / (1 << k);
		
		// T_{2^{k}}^{(0)}
		temp = 0;
		double x = a - 3 * h;
		for(int i = 0;i < (1 << (k-1));i++) {
			x += h;
			temp += f(x);
		}
		temp *= h;
		temp += 0.5 * T[k-1][0];
		T[k].push_back(temp);

		// T_{2^{k-m}}^{(m)};
		for(int m = 1;m <= k;m++) {
			// T[k-m][m];
			int p = k - m,q = m;
			temp = (1 << (2 * p)) * T[p+1][q-1] - T[p][q-1];
			temp /= (1 << (2 * p)) - 1;
			T[k-m].push_back(temp);
			if(T[k-1][1] - T[k-1][0] < EPS) return T[k-1][1];
		}
	}while(true);
}
