#include <iostream>
#include <cstddef>
#include <vector>
#include <chrono>
#include "Quantum.h"

int main() {
    try {
        // Выбираем 29 кубитов (~14 ГБ в пике работы метода Measurment)
        const size_t total_qbits = 29; 
        const size_t n_bits = 14; // Размер первого числа

        std::cout << "--- Запуск теста: 29 кубитов (~14 ГБ RAM) ---" << std::endl;
        
        // Создаем схему. Вектор состояний сразу займет 8 ГБ.
        Quantum circuit(total_qbits);

        // Определяем числа для сложения
        // Регистр 1 (кубиты 0-13): число 'a'
        // Регистр 2 (кубиты 14-28): число 'b'
        size_t a = 10000;
        size_t b = 5000;
        size_t expected = a + b;

        // Инициализация начального состояния |a>|b>
        unsigned __int128 initial_state = a | (static_cast<unsigned __int128>(b) << n_bits);
        circuit = static_cast<int>(initial_state); 

        std::cout << "Складываем a=" << a << " и b=" << b << " на 29 кубитах..." << std::endl;

        auto start = std::chrono::high_resolution_clock::now();

        // 1. Переводим ПЕРВЫЙ регистр (куда прибавляем) в базис Фурье
        // Согласно реализации Add в Quantum.cpp, CP применяется к ffirst+i (цель)
        QuantumAlgorithms::QFT(circuit, 0, n_bits - 1);

        // 2. Сложение: прибавляем второй регистр (n_bits...2*n_bits) к первому (0...n_bits-1)
        // Используем параметры: объект, ffirst, flast (цель), first, last (источник)
        QuantumAlgorithms::Add(circuit, 0, n_bits - 1, n_bits, 2 * n_bits - 1);

        // 3. Обратное QFT для первого регистра
        QuantumAlgorithms::IQFT(circuit, 0, n_bits - 1);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        std::cout << "Время вычисления гейтов: " << diff.count() << " сек." << std::endl;

        // 4. Измерение (здесь выделится еще ~6 ГБ под distribution и result)
        std::cout << "Измерение... (Ожидайте выделения памяти)" << std::endl;
        auto results = circuit.Measurment(1000000000);

        for (size_t i = 0; i < results.size(); ++i) {
            if (results[i] > 0) {
                // Результат сложения находится в первых n_bits кубитах
                size_t result_val = i & ((1ULL << n_bits) - 1);
                
                std::cout << "Результат в целевом регистре: " << result_val << std::endl;
                
                if (result_val == expected) {
                    std::cout << "УСПЕХ: " << a << " + " << b << " = " << result_val << std::endl;
                } else {
                    std::cout << "ОШИБКА: Ожидалось " << expected << ", получено " << result_val << std::endl;
                }
                break;
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "Standard Error: " << e.what() << std::endl;
    } catch (const char* e) {
        std::cerr << "Error: " << e << std::endl;
    } catch (...) {
        std::cerr << "Критическая ошибка памяти или системы!" << std::endl;
    }

    return 0;
}