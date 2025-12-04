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
	d = b*c;
	std::cout << d;
	d.H(1);
	std::cout << d;
	d = d * a;
	d.CNOT(1, 2);
	std::cout << d;
	d.CNOT(0, 1);
	std::cout << d;
}