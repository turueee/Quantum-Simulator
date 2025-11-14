#pragma once

#include <iostream>
#include <vector>
#include "TError.h"
#include "TComplex.h"
#include "TMatrix.h"


class Quantum
{
public:
	std::vector<TComplex<double>> qbits;
	size_t count;

	Quantum();
	Quantum(size_t num);
	Quantum(const Quantum& other);
	Quantum(Quantum&& other) noexcept;

	
	Quantum operator*(const Quantum& other);
	Quantum& operator=(const Quantum& other);
	TComplex<double>& operator[](size_t index);
	TComplex<double> operator[](size_t index) const;
	size_t statescount() const;

	Quantum& X(size_t qbit);//Гейт NOT
	Quantum& Y(size_t qbit);//Гейт Паули У
	Quantum& Z(size_t qbit);//Гейт Паули Z
	Quantum& H(size_t qbit);//Гейт Адамара
	Quantum& S(size_t qbit);
	Quantum& Rx(size_t qbit,double angle);//Поворот на angle радиан покруг оси X
	Quantum& Ry(size_t qbit,double angle);//Поворот на angle радиан покруг оси Y
	Quantum& Rz(size_t qbit,double angle);//Поворот на angle радиан покруг оси Z
	Quantum& P(size_t qbit,double angle);//Фазовый сдвиг
	Quantum& CNOT(int controll, int controlled);
	

	friend std::ostream& operator<<(std::ostream& out, const Quantum& other);
private:
	friend Quantum operator*(const TMatrix<TComplex<double>>& matrix,const Quantum& vector);
};
