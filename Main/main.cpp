#include <iostream>
#include <chrono>
#include <numeric>
#include "Quantum.h"

/**
 * Тест полного алгоритма Шора.
 * Факторизация числа N = 15.
 * Требуемое количество кубитов: 4n + 2 = 4*4 + 2 = 18 кубитов.
 */

int main() {
    try {
        // Число для факторизации
        size_t N = 20;
        
        std::cout << "--- Запуск алгоритма Шора для N = " << N << " ---" << std::endl;
        std::cout << "Ожидаемые делители: 7 и 9" << std::endl;

        // Замер времени всего процесса
        auto start = std::chrono::high_resolution_clock::now();

        // Вызов ShorAlgorithm из вашей библиотеки.
        // Он внутри себя последовательно выполняет:
        // 1. Проверку на четность/простоту (ShorAlgorithmFirstPhase)
        // 2. Квантовый поиск периода r (ShorAlgorithmSecondPhase)
        // 3. Классическое вычисление делителей через НОД (ShorAlgorithmThirdPhase)
        std::pair<size_t, size_t> divisors = QuantumAlgorithms::ShorAlgorithm(N);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;

        if (divisors.first != 0 && divisors.second != 0) {
            std::cout << ">>> УСПЕХ: Найдены делители: " << divisors.first 
                      << " и " << divisors.second << std::endl;
        } else {
            std::cout << ">>> ОШИБКА: Алгоритм не смог найти делители за текущие итерации." << std::endl;
        }

        std::cout << "Общее время работы: " << diff.count() << " сек." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Standard Error: " << e.what() << std::endl;
    } catch (const char* e) {
        std::cerr << "Error: " << e << std::endl;
    } catch (...) {
        std::cerr << "Критическая ошибка памяти (необходимо около 1 ГБ для 18 кубитов)!" << std::endl;
    }

    return 0;
}