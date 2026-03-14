#include <iostream>
#include <cstddef>
#include "TString.h"
#include "TComplex.h"
#include "Quantum.h"



int main() {
	Quantum q8(0);
	q8 = q8 * Quantum(0);
	q8 = q8 * Quantum(0);
	q8 = q8 * Quantum(1);

	QuantumAlgorithms::QFT(q8, 0, 3);
	std::cout << "QFT |1000>: " << q8 << std::endl;
	QuantumAlgorithms::IQFT(q8, 0, 3);
	std::cout << "IQFT |1000>: " << q8 << std::endl;
}