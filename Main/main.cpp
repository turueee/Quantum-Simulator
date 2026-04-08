#include <iostream>
#include <cstddef>
#include "Quantum.h"
#include <vector>

int main() {
    try {
        size_t n = 4;           // разрядность N (13)
        size_t x_start = 0;     // основной регистр x
        size_t aux_start = 4;   // вспомогательный регистр (n+1 кубит)
        size_t ancilla = 9;     // анцилла для CAddMod
        size_t control = 10;    // управляющий кубит

        Quantum circuit(11);    // 2n + 3 кубита

        // 1. Инициализация
        // x = 3, control = 1, aux = 0
        circuit = 3 + (1 << control); 

        std::cout << "--- Запуск теста Ua Gate ---" << std::endl;
        std::cout << "Вход: x=3, a=2, N=13, control=1" << std::endl;

        size_t a = 2;
        size_t N = 13;

        // 2. Вызов Ua_Gate (собранного по Рис. 7)
        // Внутри него: MulMod(a) -> CSwap -> MulModInverse(a_inv)
        QuantumAlgorithms::Ua_Gate(circuit, x_start, x_start + n - 1, aux_start, aux_start + n, a, N, ancilla, control);

        // 3. Измерение
        auto results = circuit.Measurment(1000);

        std::cout << "Результаты измерения:" << std::endl;
        for (size_t i = 0; i < results.size(); ++i) {
            if (results[i] > 0) {
                size_t x_val = i & 0xF;               // Первые 4 бита
                size_t aux_val = (i >> aux_start) & 0x1F; // Следующие 5 бит
                size_t ctrl_val = (i >> control) & 1;

                std::cout << "State |" << i << ">: "
                          << "Control=" << ctrl_val 
                          << ", x (Result)=" << x_val 
                          << ", aux (Should be 0)=" << aux_val 
                          << " [" << results[i] << " times]" << std::endl;
                
                // Проверка
                if (x_val == 6 && aux_val == 0) {
                    std::cout << "УСПЕХ: x перешел в 6, aux очищен!" << std::endl;
                } else {
                    std::cout << "ОШИБКА: Ожидалось x=6, aux=0" << std::endl;
                }
            }
        }

    } catch (const char* e) {
        std::cerr << "Error: " << e << std::endl;
    }
    return 0;
}