#pragma once

#include <iostream>
#include <vector>
#include <complex>
#include <bit>
#include <cstdint>
#include <numeric>
#include <random>


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
	Quantum& operator=(const int condition);
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
	Quantum& CNOT(size_t controlled, std::vector<size_t> controll);
	Quantum& CH(size_t controlled, std::vector<size_t> controll);
	Quantum& CP(size_t controlled, std::vector<size_t> controll, double angle);
	Quantum& SWAP(size_t first, size_t second);
	Quantum& CSWAP(size_t first, size_t second, size_t controll);
	void operation(const std::vector<std::complex<double>>& qop, size_t target, const std::vector<size_t>& controls);

	std::vector<int> Measurment(size_t count_of_measurment);
	

	friend std::ostream& operator<<(std::ostream& out, const Quantum& other);
};

class QuantumAlgorithms
{
public:
	static double getQFTPhase(size_t distance);
	static size_t modInverse(size_t a, size_t N);
	static Quantum& QFT(Quantum& object,int first,int last);
	static Quantum& IQFT(Quantum& object, size_t first, size_t last);
	static Quantum& Add(Quantum& object, size_t ffirst, size_t flast, size_t first, size_t last);
	static Quantum& Add(Quantum& object, size_t first, size_t last, size_t num);
	static Quantum& CAdd(Quantum& object, size_t first, size_t last, size_t num, std::vector<size_t> controll);
	static Quantum& CAddMod(Quantum& object, size_t first,size_t last, size_t add,size_t mod, size_t ancilla, std::vector<size_t> controll);
	static Quantum& Sub(Quantum& object, size_t ffirst, size_t flast, size_t first, size_t last);
	static Quantum& Sub(Quantum& object, size_t first, size_t last, size_t num);
	static Quantum& CSub(Quantum& object, size_t first, size_t last, size_t num, std::vector<size_t> controll);
	static Quantum& MulMod(Quantum& object, size_t first, size_t last, size_t xfirst, size_t xlast, size_t a, size_t N, size_t ancilla, size_t controll);
	static Quantum& Ua_Gate(Quantum &object, size_t xfirst, size_t xlast, size_t afirst, size_t alast, size_t a, size_t N, size_t ancilla, size_t controll);
	static Quantum& СSWAP(Quantum& object, size_t first, size_t last, size_t afirst, size_t alast, size_t controll);
	static bool ShorAlgorithm(size_t number);
	static bool ShorAlgorithmFirstPhase(size_t number);
	static bool ShorAlgorithmSecondPhase(size_t number);
};
