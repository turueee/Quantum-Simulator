#include <iostream>
#include <chrono>
#include <numeric>
#include "Quantum.h"

#include <iostream>
#include <string>
#include "Quantum.h"

int main(int argc, char* argv[]) 
{
    size_t N = std::stoull(argv[1]);
    auto divisors = QuantumAlgorithms::ShorAlgorithm(N);
    std::cout << "Делители: " << divisors.first << " и " << divisors.second << std::endl;

    return 0;
}