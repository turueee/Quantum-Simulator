#include "Quantum.h"
#include <iostream>
#include <chrono>
#include <omp.h>

// Вспомогательная функция для установки классического значения в регистр с помощью X-гейтов
void SetRegisterValue(Quantum& q, size_t start_qbit, size_t end_qbit, size_t value) {
    for (size_t i = 0; i <= (end_qbit - start_qbit); ++i) {
        if ((value >> i) & 1) {
            q.X(start_qbit + i);
        }
    }
}

int main() {
    // Ограничиваем количество потоков до 6
    omp_set_num_threads(6);

    size_t total_qbits = 29;
    
    // Границы первого регистра (целевой, к которому прибавляем)
    size_t target_first = 0;
    size_t target_last = 13;
    size_t target_value = 100;

    // Границы второго регистра (тот, который прибавляем)
    size_t source_first = 14;
    size_t source_last = 27;
    size_t source_value = 42;

    size_t measurements_count = 1000;

    std::cout << "[INFO] Потоков OpenMP: " << omp_get_max_threads() << std::endl;
    std::cout << "[INFO] Инициализация среды на " << total_qbits << " кубитов (~8.5 ГБ ОЗУ)...\n\n";

    // ==========================================
    // ТЕСТ 1: ЧИСТОЕ ВЫПОЛНЕНИЕ СЛОЖЕНИЯ РЕГИСТРОВ
    // ==========================================
    std::cout << "--- ТЕСТ 2: Выполнение + Измерение результата ---" << std::endl;
    
    Quantum q2(total_qbits);
    
    SetRegisterValue(q2, target_first, target_last, target_value);
    SetRegisterValue(q2, source_first, source_last, source_value);
    
    auto start2 = std::chrono::high_resolution_clock::now();
    
    // Те же самые квантовые операции
    {
    QuantumAlgorithms::QFT(q2, target_first, target_last);
    QuantumAlgorithms::Add(q2, target_first, target_last, source_first, source_last);
    QuantumAlgorithms::IQFT(q2, target_first, target_last);
    }
    
    // Измерение
    std::vector<int> result = q2.Measurment(measurements_count); 
    
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff2 = end2 - start2;
    
    std::cout << "Время (Гейты + вычисление распределения + " << measurements_count << " шотов): " 
              << diff2.count() << " секунд\n" << std::endl;

    return 0;
}