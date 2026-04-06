#include <iostream>
#include <cstddef>
#include "Quantum.h"



int main() {
    Quantum q(3); 

    size_t first = 0;
    size_t last = 2;
    size_t ancilla = 3;
    
    size_t add = 2;
    size_t mod = 3;
    
    q.X(1); 
    std::cout<<q<<std::endl;
    QuantumAlgorithms::QFT(q, first, last);
    std::cout<<q<<std::endl;
    
    QuantumAlgorithms::AddMod(q, first, last, add, mod, ancilla);
    std::cout<<q<<std::endl;
    QuantumAlgorithms::IQFT(q, first, last);
    std::cout<<q<<std::endl;
    return 0;
}