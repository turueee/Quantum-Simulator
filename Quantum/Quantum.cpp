#include "Quantum.h"
#include <cmath>

Quantum::Quantum():qbits(),count(1){}

Quantum::Quantum(size_t num)
{
	if (num != 0 && num != 1)
		throw;
	if (num == 0)
		qbits = { TComplex<double>(1.0),TComplex<double>(0.0) };
	else
		qbits = { TComplex<double>(0.0),TComplex<double>(1.0) };
	count = 1;
}

Quantum::Quantum(const Quantum& other)
{
	count = other.count;
	qbits = other.qbits;
}

Quantum::Quantum(Quantum&& other) noexcept
{
	count = other.count;
	qbits = std::move(other.qbits);
	other.count = 0;
}

Quantum Quantum::operator*(const Quantum& other)
{
	Quantum res;
	res.qbits.resize(std::pow(2, count + other.count));
	res.count = count + other.count;
	for (size_t i = 0; i < qbits.size(); ++i)
		for (size_t j = 0; j < other.qbits.size(); ++j)
			res.qbits[i * other.qbits.size() + j] = qbits[i] * other.qbits[j];
	return res;
}

Quantum& Quantum::operator=(const Quantum& other)
{
	qbits = other.qbits;
	count = other.count;
	return *this;
}

TComplex<double>& Quantum::operator[](size_t index)
{
	return qbits[index];
}

TComplex<double> Quantum::operator[](size_t index) const
{
	return qbits[index];
}

size_t Quantum::statescount() const
{
	return qbits.size();
}

Quantum& Quantum::X()
{
	TMatrix<TComplex<double>> HH(2, 2);

	HH[0][0] = 0;
	HH[0][1] = 1;
	HH[1][0] = 1;
	HH[1][1] = 0;

	TMatrix<TComplex<double>> I(2, 2);
	I[0][0] = 1;
	I[0][1] = 0;
	I[1][0] = 0;
	I[1][1] = 1;

	TMatrix<TComplex<double>> fullMatrix = HH;

	for (size_t i = 0; i < count - 1; ++i) {
		fullMatrix = I.TenzorMul(fullMatrix);
	}

	*this = fullMatrix * (*this);
	return *this;
}

Quantum& Quantum::Y()
{
	TMatrix<TComplex<double>> HH(2, 2);

	HH[0][0] = 0;
	HH[0][1] = TComplex<double>(0.0,-1.0);
	HH[1][0] = TComplex<double>(0.0, 1.0);
	HH[1][1] = 0;

	TMatrix<TComplex<double>> I(2, 2);
	I[0][0] = 1;
	I[0][1] = 0;
	I[1][0] = 0;
	I[1][1] = 1;

	TMatrix<TComplex<double>> fullMatrix = HH;

	for (size_t i = 0; i < count - 1; ++i) {
		fullMatrix = I.TenzorMul(fullMatrix);
	}

	*this = fullMatrix * (*this);
	return *this;
}

Quantum& Quantum::Z()
{
	TMatrix<TComplex<double>> HH(2, 2);

	HH[0][0] = 1;
	HH[0][1] = 0;
	HH[1][0] = 0;
	HH[1][1] = -1;

	TMatrix<TComplex<double>> I(2, 2);
	I[0][0] = 1;
	I[0][1] = 0;
	I[1][0] = 0;
	I[1][1] = 1;

	TMatrix<TComplex<double>> fullMatrix = HH;

	for (size_t i = 0; i < count - 1; ++i) {
		fullMatrix = I.TenzorMul(fullMatrix);
	}

	*this = fullMatrix * (*this);
	return *this;
}

Quantum& Quantum::H()
{
	TMatrix<TComplex<double>> HH(2, 2);

	HH[0][0] = 1 / sqrt(2);
	HH[0][1] = 1 / sqrt(2);
	HH[1][0] = 1 / sqrt(2);
	HH[1][1] = -1 / sqrt(2);

	TMatrix<TComplex<double>> I(2, 2);
	I[0][0] = 1;
	I[0][1] = 0;
	I[1][0] = 0;
	I[1][1] = 1;

	TMatrix<TComplex<double>> fullMatrix = HH;

	for (size_t i = 0; i < count-1; ++i) {
		fullMatrix = I.TenzorMul(fullMatrix);
	}

	*this = fullMatrix * (*this);
	return *this;
}

Quantum& Quantum::S()
{
	TMatrix<TComplex<double>> HH(2, 2);

	HH[0][0] = 1;
	HH[0][1] = 0;
	HH[1][0] = 0;
	HH[1][1] = TComplex <double>(0.0,1.0) ;

	TMatrix<TComplex<double>> I(2, 2);
	I[0][0] = 1;
	I[0][1] = 0;
	I[1][0] = 0;
	I[1][1] = 1;

	TMatrix<TComplex<double>> fullMatrix = HH;

	for (size_t i = 0; i < count - 1; ++i) {
		fullMatrix = I.TenzorMul(fullMatrix);
	}

	*this = fullMatrix * (*this);
	return *this;
}

Quantum& Quantum::Rx(double angle)
{
	TMatrix<TComplex<double>> HH(2, 2);

	HH[0][0] = cos(angle/2.0);
	HH[0][1] = TComplex<double>(0.0, -sin(angle/2.0));
	HH[1][0] = TComplex<double>(0.0, -sin(angle / 2.0));
	HH[1][1] = cos(angle / 2.0);

	TMatrix<TComplex<double>> I(2, 2);
	I[0][0] = 1;
	I[0][1] = 0;
	I[1][0] = 0;
	I[1][1] = 1;

	TMatrix<TComplex<double>> fullMatrix = HH;

	for (size_t i = 0; i < count - 1; ++i) {
		fullMatrix = I.TenzorMul(fullMatrix);
	}

	*this = fullMatrix * (*this);
	return *this;
}

Quantum& Quantum::Ry(double angle)
{
	TMatrix<TComplex<double>> HH(2, 2);

	HH[0][0] = cos(angle / 2.0);
	HH[0][1] = -sin(angle/2.0);
	HH[1][0] = sin(angle/2.0);
	HH[1][1] = cos(angle / 2.0);

	TMatrix<TComplex<double>> I(2, 2);
	I[0][0] = 1;
	I[0][1] = 0;
	I[1][0] = 0;
	I[1][1] = 1;

	TMatrix<TComplex<double>> fullMatrix = HH;

	for (size_t i = 0; i < count - 1; ++i) {
		fullMatrix = I.TenzorMul(fullMatrix);
	}

	*this = fullMatrix * (*this);
	return *this;
}

Quantum& Quantum::Rz(double angle)
{
	TMatrix<TComplex<double>> HH(2, 2);

	HH[0][0] = TComplex < double >(cos(angle/2),sin(angle/2));
	HH[0][1] = 0;
	HH[1][0] = 0;
	HH[1][1] = TComplex < double >(cos(angle / 2), sin(angle / 2));

	TMatrix<TComplex<double>> I(2, 2);
	I[0][0] = 1;
	I[0][1] = 0;
	I[1][0] = 0;
	I[1][1] = 1;

	TMatrix<TComplex<double>> fullMatrix = HH;

	for (size_t i = 0; i < count - 1; ++i) {
		fullMatrix = I.TenzorMul(fullMatrix);
	}

	*this = fullMatrix * (*this);
	return *this;
}

Quantum& Quantum::P(double angle)
{
	TMatrix<TComplex<double>> HH(2, 2);

	HH[0][0] = 1;
	HH[0][1] = 0;
	HH[1][0] = 0;
	HH[1][1] = TComplex < double >(cos(angle), sin(angle));

	TMatrix<TComplex<double>> I(2, 2);
	I[0][0] = 1;
	I[0][1] = 0;
	I[1][0] = 0;
	I[1][1] = 1;

	TMatrix<TComplex<double>> fullMatrix = HH;

	for (size_t i = 0; i < count - 1; ++i) {
		fullMatrix = I.TenzorMul(fullMatrix);
	}

	*this = fullMatrix * (*this);
	return *this;
}

Quantum& Quantum::CNOT(int controll, int controlled)
{
	if (controll >= count || controlled >= count)
		throw;

	TMatrix<TComplex<double>> a(std::pow(2, count), std::pow(2, count));
	for (size_t i = 0; i < a.GetColumns(); ++i)
		a[i][i] = 1;

	std::vector<int> bits;
	for (size_t i = 0; i < a.GetColumns(); ++i)
	{
		int num = i;
		if (num < std::pow(2, controll))
			num = 0;
		num /= std::pow(2, controll);
		num %= 2;

		if (num == 1)
			bits.push_back(i);
	}

	TMatrix<TComplex<double>> X(2, 2);
	X[0][0] = 0;
	X[0][1] = 1;
	X[1][0] = 1;
	X[1][1] = 0;

	TMatrix<TComplex<double>> I(2, 2);
	I[0][0] = 1;
	I[0][1] = 0;
	I[1][0] = 0;
	I[1][1] = 1;


	TMatrix<TComplex<double>> fullMatrix = I;
	for (int pos = count - 1; pos >= 0; --pos) {
		if (pos == controlled) {
			fullMatrix = X.TenzorMul(fullMatrix);
		}
		else {
			fullMatrix = I.TenzorMul(fullMatrix);
		}
	}

	for (size_t i = 0; i < bits.size(); ++i)
	{
		int state_index = bits[i];
		for (size_t j = 0; j < a.GetColumns(); ++j)
		{
			a[state_index][j] = fullMatrix[state_index][j];
		}
	}

	*this = a * (*this);
	return *this;
}

std::ostream& operator<<(std::ostream& out, const Quantum& other)
{
	out << "[";
	for (size_t i = 0; i < other.statescount(); ++i) {
		out << other[i];
		if (i < other.statescount() - 1) {
			out << "; ";
		}
	}
	out << ">\n";
	return out;
}

Quantum operator*(const TMatrix<TComplex<double>>& matrix, const Quantum& vector)
{
	Quantum res;
	res.qbits.resize(matrix.GetRows(), TComplex<double>(0.0));
	res.count = vector.count;

	for (size_t i = 0; i < matrix.GetRows(); ++i)
	{
		for (size_t j = 0; j < matrix.GetColumns(); ++j)
		{
			res.qbits[i] += matrix[i][j] * vector[j];
		}
	}
	return res;
}