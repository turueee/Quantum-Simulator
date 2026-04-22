#include <iostream>
#include <chrono>
#include <numeric>
#include "Quantum.h"

// int main() {
//     try {
//         // N = 323 (17 * 19). 
//         // 323 в двоичном виде занимает 9 бит.
//         // Количество кубитов: 2*9 + 3 = 21 кубит.
//         size_t N = 323;

//         std::cout << "=== Тестирование алгоритма Шора ===\n";
//         std::cout << "Факторизуемое число: N = " << N << "\n";
//         std::cout << "Ожидаемое количество кубитов: 21\n\n";

//         size_t r = 0;
//         size_t a = 0;
//         int attempts = 0;

//         // Засекаем общее время
//         auto start_time = std::chrono::high_resolution_clock::now();

//         // Крутим цикл, пока не найдем подходящие параметры
//         while (true) {
//             attempts++;
//             std::cout << "[Попытка " << attempts << "] Запуск квантовой фазы...\n";

//             // Вызываем вторую фазу. Она сама выберет 'a', построит цепь на 21 кубит 
//             // и вернет пару: {период r, выбранное a}
//             std::pair<size_t, size_t> result = QuantumAlgorithms::ShorAlgorithmSecondPhase(N);
//             r = result.first;
//             a = result.second;

//             std::cout << "  Выбрано случайное a = " << a << "\n";

//             // Проверка 1: Может нам повезло классически в 1-й фазе?
//             if (std::gcd(a, N) > 1) {
//                 std::cout << "  -> Удача! Найден классический общий делитель.\n";
//                 break;
//             }

//             // Проверка 2: Нашел ли квантовый алгоритм какой-то период?
//             if (r == 0) {
//                 std::cout << "  -> Период не найден (измерен 0). Повтор...\n";
//                 continue;
//             }

//             std::cout << "  -> Квантовый симулятор измерил период r = " << r << "\n";

//             // Проверка 3: Для успешной факторизации период должен быть четным
//             if (r % 2 != 0) {
//                 std::cout << "  -> Период нечетный. Повтор...\n";
//                 continue;
//             }

//             // Проверка 4: Исключаем тривиальный случай a^(r/2) = -1 mod N
//             size_t half_power = QuantumAlgorithms::modPow(a, r / 2, N);
//             if (half_power == N - 1) {
//                 std::cout << "  -> Тривиальный случай a^(r/2) = -1. Повтор...\n";
//                 continue;
//             }

//             // Если все проверки пройдены, выходим из цикла — мы готовы найти множители!
//             break;
//         }

//         auto end_time = std::chrono::high_resolution_clock::now();
//         std::chrono::duration<double> diff = end_time - start_time;

//         // === ФАЗА 3: Подведение итогов ===
//         std::cout << "\n=== ИТОГИ ФАКТОРИЗАЦИИ ===\n";
//         std::cout << "Затрачено времени: " << diff.count() << " сек.\n";
//         std::cout << "Количество попыток: " << attempts << "\n";

//         size_t p = 0, q = 0;

//         if (std::gcd(a, N) > 1) {
//             p = std::gcd(a, N);
//             q = N / p;
//             std::cout << "Метод: Классический (удача генератора)\n";
//         } else {
//             size_t half_power = QuantumAlgorithms::modPow(a, r / 2, N);
//             p = std::gcd(half_power - 1, N);
//             q = std::gcd(half_power + 1, N);
//             std::cout << "Метод: Квантовый (Шор)\n";
//         }

//         std::cout << "Найденные делители: " << p << " и " << q << "\n";
        
//         if (p * q == N && p > 1 && q > 1) {
//             std::cout << "СТАТУС: УСПЕХ! (" << p << " * " << q << " = " << N << ")\n";
//         } else {
//             std::cout << "СТАТУС: ОШИБКА!\n";
//         }

//     } catch (const std::exception& e) {
//         std::cerr << "Standard Error: " << e.what() << std::endl;
//     } catch (const char* e) {
//         std::cerr << "Error: " << e << std::endl;
//     }

//     return 0;
// }

#include <iostream>
#include <numeric>
#include <iomanip>
#include "Quantum.h"

int main() {
    // Настройка для красивого вывода
    std::cout << std::fixed << std::setprecision(2);
    
    size_t N = 15;
    std::cout << "========================================" << std::endl;
    std::cout << "   ДИАГНОСТИКА АЛГОРИТМА ШОРА (N=15)    " << std::endl;
    std::cout << "========================================" << std::endl;

    int attempt = 0;
    while (attempt < 10) { // Сделаем 10 пробных запусков
        attempt++;
        std::cout << "\n[ПОПЫТКА " << attempt << "]" << std::endl;

        // Вызываем вторую фазу (вернет {r, a})
        auto result = QuantumAlgorithms::ShorAlgorithmSecondPhase(N);
        size_t r = result.first;
        size_t a = result.second;

        // ВАЖНО: Внутри ShorAlgorithmSecondPhase добавь вывод переменной y!
        // Но пока посмотрим на то, что пришло сюда:
        std::cout << "  Выбрано a: " << a << std::endl;
        
        // 1. Проверка на мгновенный успех
        size_t common = std::gcd(a, N);
        if (common > 1) {
            std::cout << "  (!) Случайно найден делитель через GCD: " << common << std::endl;
            continue;
        }

        std::cout << "  Результат квантовой фазы (период r): " << r << std::endl;

        // 2. Анализ периода
        if (r == 0) {
            std::cout << "  [!] ОШИБКА: Измерен нулевой период. Проверь запутанность в Ua_Gate." << std::endl;
        } 
        else if (r % 2 != 0) {
            std::cout << "  [-] Период нечетный (" << r << "), для Шора не подходит." << std::endl;
        } 
        else {
            // 3. Пытаемся найти множители
            size_t val = QuantumAlgorithms::modPow(a, r / 2, N);
            if (val == N - 1) {
                std::cout << "  [-] Тривиальный случай (a^r/2 == -1). Нужен перезапуск." << std::endl;
            } else {
                size_t p = std::gcd(val - 1, N);
                size_t q = std::gcd(val + 1, N);
                if (p * q == N && p > 1) {
                    std::cout << "  [+++] УСПЕХ! Делители: " << p << " и " << q << std::endl;
                    return 0; // Выходим при первом реальном успехе
                } else {
                    std::cout << "  [?] Период " << r << " найден, но делители не извлеклись." << std::endl;
                }
            }
        }
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "Тест завершен после 10 попыток." << std::endl;
    return 0;
}