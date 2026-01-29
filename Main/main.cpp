#include <iostream>
#include <cstddef>
#include "TString.h"
#include "TComplex.h"
#include "Quantum.h"



int main()
{
	Quantum a(0.6, 0.8);
	Quantum b(0);
	Quantum c(0);
	Quantum d;
	d = c*b;
	std::cout << d;
	d.H(0);
	std::cout << d;
	d.CNOT(0, 1);
	std::cout << d;
	d = d * a;
	std::cout << d;
	d.CNOT(0, 1);
	std::cout << d;
	d.H(0);
	std::cout << d;
	std::vector<int> meas = d.Measurment(1000);
	for (size_t i = 0; i < meas.size(); ++i)
		std::cout << meas[i] << ' ';
	std::cout << endl;
	Quantum o(0);
	o.H(0);
	std::vector<int> measu = o.Measurment(100);
	for (size_t i = 0; i < measu.size(); ++i)
		std::cout << measu[i] << ' ';
	std::cout << endl;
}