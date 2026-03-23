#include <iostream>
#include <cstddef>
#include "Quantum.h"



int main() {
    // ТЕСТ 1: Сложение (1 + 2 = 3)
    {
        Quantum q(4);
        q.X(0); 
        q.X(3); 
		std::cout << q << std::endl;
        
        QuantumAlgorithms::QFT(q, 0, 1);
		std::cout << q << std::endl;
        QuantumAlgorithms::Add(q, 0, 1, 2, 3);
		std::cout << q << std::endl;
        QuantumAlgorithms::IQFT(q, 0, 1);
		std::cout << q << std::endl;
    }

    // ТЕСТ 2: Вычитание (3 - 1 = 2)
    {
        Quantum q(4);
        q.X(0); q.X(1); 
        q.X(2);         
		std::cout << q << std::endl;
        
        QuantumAlgorithms::QFT(q, 0, 1);
		std::cout << q << std::endl;
        QuantumAlgorithms::Sub(q, 0, 1, 2, 3);
		std::cout << q << std::endl;
        QuantumAlgorithms::IQFT(q, 0, 1);
		std::cout << q << std::endl;
    }

    // ТЕСТ 3: Переполнение (3 + 1 = 0 mod 4)
    {
        Quantum q(4);
        q.X(0); q.X(1); 
        q.X(2);  
		std::cout << q << std::endl;       
        
        QuantumAlgorithms::QFT(q, 0, 1);
		std::cout << q << std::endl;
        QuantumAlgorithms::Add(q, 0, 1, 2, 3);
		std::cout << q << std::endl;
        QuantumAlgorithms::IQFT(q, 0, 1);
        
        std::cout << q << std::endl;
    }

    return 0;
}