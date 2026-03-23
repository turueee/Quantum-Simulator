#pragma once

#include <iostream>
#include <vector>
#include <complex>


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

	Quantum& X(size_t qbit);//���� NOT
	Quantum& Y(size_t qbit);//���� ����� �
	Quantum& Z(size_t qbit);//���� ����� Z
	Quantum& H(size_t qbit);//���� �������
	Quantum& S(size_t qbit);
	Quantum& Rx(size_t qbit,double angle);//������� �� angle ������ ������ ��� X
	Quantum& Ry(size_t qbit,double angle);//������� �� angle ������ ������ ��� Y
	Quantum& Rz(size_t qbit,double angle);//������� �� angle ������ ������ ��� Z
	Quantum& P(size_t qbit,double angle);//���� ����
	Quantum& CNOT(size_t controll, size_t controlled);
	Quantum& CH(size_t controll, size_t controlled);
	Quantum& CP(size_t controll, size_t controlled, double angle);
	void operation(std::vector<std::complex<double>>& qop, std::vector<size_t> qbit);

	std::vector<int> Measurment(size_t count_of_measurment);
	

	friend std::ostream& operator<<(std::ostream& out, const Quantum& other);
};

class QuantumAlgorithms
{
public:
	static double getQFTPhase(size_t distance);
	static Quantum& QFT(Quantum& object,int first,int last);
	static Quantum& IQFT(Quantum& object, size_t first, size_t last);
	static Quantum& Add(Quantum& object,size_t ffirst,size_t flast,size_t first,size_t last);
	static Quantum& Sub(Quantum& object,size_t ffirst,size_t flast,size_t first,size_t last);
};
