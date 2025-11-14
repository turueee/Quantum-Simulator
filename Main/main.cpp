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
	d = a;
	std::cout << d;
	d.Ry(1,3);
	std::cout << d;
	d.Rz(1, 0.5);
	std::cout << d;
}