#include <iostream>
#include <cstddef>
#include "TString.h"
#include "TComplex.h"
#include "Quantum.h"



int main() {
	Quantum q8(1);
	q8 = q8 * Quantum(0);
	q8 = q8 * Quantum(0);
	q8 = q8 * Quantum(0);
	std::cout << q8 << std::endl;

	std::vector<int> v = q8.Measurment(1000);
	for (size_t i = 0; i < v.size(); ++i)
		std::cout << v[i] << ' ';

	q8.H(3);

	QuantumAlgorithms::QFT(q8, 0, 3);
	std::cout << "QFT |1000>: " << q8 << std::endl;

	QuantumAlgorithms::IQFT(q8, 0, 3);
	std::cout << "IQFT |1000>: " << q8 << std::endl;
}