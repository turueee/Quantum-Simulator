#include <iostream>
#include <cstddef>
#include "TString.h"
#include "Quantum.h"



int main()
{
	Quantum a(0);
	Quantum b(0);
	Quantum c(0);
	Quantum d;
	d = a*b;
	std::cout << d;
	d.H(0);
	std::cout << d;
	d.H(1);
	std::cout << d;
	d.CNOT(0, 1);
	std::cout << d;
	d.H(0);
	std::cout << d;
	d.H(1);
	std::cout << d;
}