#include <iostream>
#include <cstddef>
#include "Quantum.h"



int main() 
{
    Quantum qbit(3);
    std::cout<<qbit<<std::endl;
    qbit.X(1);
    std::cout<<qbit<<std::endl;
    QuantumAlgorithms::QFT(qbit,1,2);
    std::cout<<qbit<<std::endl;
    QuantumAlgorithms::AddMod(qbit,1,2,1,2,0);
    //QuantumAlgorithms::Sub(qbit,1,2,1);
    std::cout<<qbit<<std::endl;
    QuantumAlgorithms::IQFT(qbit,1,2);
    std::cout<<qbit<<std::endl;
    return 0;
}