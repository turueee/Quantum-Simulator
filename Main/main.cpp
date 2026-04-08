#include <iostream>
#include <cstddef>
#include "Quantum.h"
#include <vector>

int main() {
    try {
        // Параметры системы
        size_t n = 4;           // разрядность N (13)
        size_t x_start = 0;     // регистр x: 0, 1, 2, 3
        size_t b_start = 4;     // регистр b: 4, 5, 6, 7, 8 (n+1 кубит)
        size_t ancilla = 9;     // анцилла
        size_t control = 10;    // управляющий кубит
        
        Quantum circuit(11); // Всего 11 кубитов (2n+3)

        // 1. Инициализация состояний
        // x = 3 (состояние |3>)
        circuit = 3; 
        
        // Включаем управляющий кубит (бит 10)
        // Индекс состояния будет 3 + (1 << 10) = 1027
        circuit = 3 + (1 << control); 

        std::cout << "Начальное состояние (x=3, control=1, b=0):" << std::endl;

        // 2. Выполнение умножения: (3 * 2) mod 13
        size_t a = 2;
        size_t N = 13;
        
        // В твоем MulMod: (object, b_first, b_last, x_first, x_last, a, N, ancilla, control)
        QuantumAlgorithms::MulMod(circuit, b_start, b_start + n, x_start, x_start + n - 1, a, N, ancilla, control);

        std::cout << "После MulMod:" << std::endl;

        // 3. Измерение
        auto results = circuit.Measurment(1000);
        
        std::cout << "Результаты (анализируем регистр b, кубиты 4-8):" << std::endl;
        for (size_t i = 0; i < results.size(); ++i) {
            if (results[i] > 0) {
                // Извлекаем значение регистра b (сдвигаем результат вправо на b_start)
                size_t b_val = (i >> b_start) & 0x1F; // 5 бит регистра b
                size_t x_val = i & 0xF;               // 4 бита регистра x
                size_t ctrl_val = (i >> control) & 1; // бит контроля
                
                std::cout << "State |" << i << ">: "
                          << "Control=" << ctrl_val 
                          << ", x=" << x_val 
                          << ", b (Result)=" << b_val 
                          << " [" << results[i] << " times]" << std::endl;
            }
        }

    } catch (const char* e) {
        std::cerr << "Error: " << e << std::endl;
    }

    return 0;
}