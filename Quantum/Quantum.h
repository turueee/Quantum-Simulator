#pragma once

#include <iostream>
#include <vector>
#include <complex>
#include "TError.h"
#include "TMatrix.h"


class Quantum
{
public:
	std::vector<std::complex<double>> qbits;
	size_t count;

	Quantum();
	Quantum(size_t num);
	Quantum(const std::complex<double>& a, const std::complex<double>& b);
	Quantum(const Quantum& other);
	Quantum(Quantum&& other) noexcept;

	
	Quantum operator*(const Quantum& other);
	Quantum& operator=(const Quantum& other);
	std::complex<double>& operator[](size_t index);
	std::complex<double> operator[](size_t index) const;
	size_t statescount() const;

	Quantum& X(size_t qbit);//Гейт NOT
	Quantum& Y(size_t qbit);//Гейт Паули У
	Quantum& Z(size_t qbit);//Гейт Паули Z
	Quantum& H(size_t qbit);//Гейт Адамара
	Quantum& S(size_t qbit);
	Quantum& Rx(size_t qbit,double angle);//Поворот на angle радиан покруг оси X
	Quantum& Ry(size_t qbit,double angle);//Поворот на angle радиан покруг оси Y
	Quantum& Rz(size_t qbit,double angle);//Поворот на angle радиан покруг оси Z
	Quantum& P(size_t qbit,double angle);//Гейт фазы
	Quantum& CNOT(size_t controll, size_t controlled);
	Quantum& CH(size_t controll, size_t controlled);
	Quantum& CP(size_t controll, size_t controlled, double angle);
	void operation(std::vector<std::complex<double>>& qop, std::vector<size_t> qbit);

	std::vector<int> Measurment(size_t count_of_measurment);
	

	friend std::ostream& operator<<(std::ostream& out, const Quantum& other);
private:
	friend Quantum operator*(const TMatrix<std::complex<double>>& matrix, const Quantum& vector);
};

class QuantumAlgorithms
{
public:
	static double getQFTPhase(size_t distance);
	static Quantum& QFT(Quantum& object,size_t first,size_t last);
	static Quantum& IQFT(Quantum& object, size_t first, size_t last);

};
