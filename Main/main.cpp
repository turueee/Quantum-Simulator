#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include "Quantum.h"
#include <thread>

/**
 * Тест производительности квантового сложения (регистр + регистр)
 * на 29 кубитах.
 */

int main() {
    try {
        unsigned int n = std::thread::hardware_concurrency();
        std::cout << "Доступно логических процессоров: " << n << std::endl;
        // Конфигурация: используем максимум 29 кубитов
        const size_t total_qbits = 29;
        const size_t n_bits = 14; // Размер каждого числа (14 + 14 = 28 кубитов + 1 запасной)

        // Распределение кубитов
        size_t f_first = 0;
        size_t f_last = n_bits - 1;      // Регистр 1 (куда прибавляем): 0-13 кубиты
        size_t s_first = n_bits;
        size_t s_last = 2 * n_bits - 1;  // Регистр 2 (что прибавляем): 14-27 кубиты

        std::cout << "--- Запуск теста: Сложение регистров на 29 кубитах ---" << std::endl;
        std::cout << "Выделение памяти: ~8.5 ГБ под вектор состояний..." << std::endl;

        // 1. Создаем квантовую систему
        Quantum circuit(total_qbits);

        // 2. Определяем числа для сложения
        size_t a = 1234;  // Число в первом регистре
        size_t b = 5678;  // Число во втором регистре
        size_t expected = a + b;

        // Инициализация начального состояния |a>|b>
        // Используем сдвиг для записи числа b во второй регистр
        unsigned __int128 initial_state = a | (static_cast<unsigned __int128>(b) << n_bits);
        circuit = static_cast<int>(initial_state); 

        std::cout << "Складываем a=" << a << " (рег.1) и b=" << b << " (рег.2)..." << std::endl;

        auto start = std::chrono::high_resolution_clock::now();

        // 3. АЛГОРИТМ:
        // Переводим ПЕРВЫЙ регистр (цель) в базис Фурье
        QuantumAlgorithms::QFT(circuit, f_first, f_last);

        // Выполняем сложение двух регистров
        // Параметры: (объект, f_first, f_last, s_first, s_last)
        QuantumAlgorithms::Add(circuit, f_first, f_last, s_first, s_last);

        // Возвращаем первый регистр в вычислительный базис
        QuantumAlgorithms::IQFT(circuit, f_first, f_last);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;

        std::cout << "Время выполнения гейтов: " << std::fixed << std::setprecision(4) << diff.count() << " сек." << std::endl;

        // 4. ИЗМЕРЕНИЕ
        std::cout << "Измерение результата (требуется RAM для распределения)..." << std::endl;
        auto results = circuit.Measurment(100);

        for (size_t i = 0; i < results.size(); ++i) {
            if (results[i] > 0) {
                // Результат суммы находится в первых n_bits кубитах (0-13)
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
    } catch (...) {
        std::cerr << "Критическая ошибка (проверьте наличие 16 ГБ RAM для Measurment)!" << std::endl;
    }

    return 0;
}