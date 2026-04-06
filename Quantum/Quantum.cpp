#include "Quantum.h"
#include <cmath>
#include <chrono>
#include <random>
#include <numbers>

Quantum::Quantum():qbits(),count(1){}

Quantum::Quantum(size_t num)
{
	count = num;
	qbits.resize(1<<num,0);
	qbits[0] = 1;
}

Quantum::Quantum(const std::complex<double>& a, const std::complex<double>& b)
{
	if (std::abs(a) * std::abs(a) + std::abs(b) * std::abs(b) != 1)
		throw "not qbit";
	qbits = { std::complex<double>(a),std::complex<double>(b) };
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

Quantum &Quantum::operator=(const int condition)
{
    if (condition>=qbits.size())
	{
		throw " ";
	}
	for (size_t i = 0;i<qbits.size();++i)
		qbits[i] = 0;
	qbits[condition] = std::complex<double>(1.0,0.0);
	return *this;
}

std::complex<double>& Quantum::operator[](size_t index)
{
	return qbits[index];
}

std::complex<double> Quantum::operator[](size_t index) const
{
	return qbits[index];
}

size_t Quantum::statescount() const
{
	return qbits.size();
}

Quantum& Quantum::X(size_t qbit)
{
	std::vector<std::complex<double>> X(4);

	X[0] = 0;
	X[1] = 1;
	X[2] = 1;
	X[3] = 0;
	operation(X, { qbit });
	return *this;
}

Quantum& Quantum::Y(size_t qbit)
{
	std::vector<std::complex<double>> Y(4);

	Y[0] = 0;
	Y[1] = std::complex<double>(0.0, -1.0);
	Y[2] = std::complex<double>(0.0, 1.0);
	Y[3] = 0;
	operation(Y, { qbit });
	return *this;
}

Quantum& Quantum::Z(size_t qbit)
{
	std::vector<std::complex<double>> Z(4);

	Z[0] = 1;
	Z[1] = 0;
	Z[2] = 0;
	Z[3] = -1;

	operation(Z, { qbit });
	return *this;
}

Quantum& Quantum::H(size_t qbit)
{
	std::vector<std::complex<double>> H(4);

	H[0] = 1 / sqrt(2);
	H[1] = 1 / sqrt(2);
	H[2] = 1 / sqrt(2);
	H[3] = -1 / sqrt(2);

	operation(H, { qbit });
	return *this;
}

Quantum& Quantum::S(size_t qbit)
{
	std::vector<std::complex<double>> S(4);

	S[0] = 1;
	S[1] = 0;
	S[2] = 0;
	S[3] = std::complex <double>(0.0,1.0) ;

	operation(S, { qbit });
	return *this;
}

Quantum& Quantum::Rx(size_t qbit,double angle)
{
	std::vector<std::complex<double>> R(4);

	R[0] = cos(angle/2.0);
	R[1] = std::complex<double>(0.0, -sin(angle/2.0));
	R[2] = std::complex<double>(0.0, -sin(angle / 2.0));
	R[3] = cos(angle / 2.0);

	operation(R, { qbit });
	return *this;
}

Quantum& Quantum::Ry(size_t qbit,double angle)
{
	std::vector<std::complex<double>> R(4);

	R[0] = cos(angle / 2.0);
	R[1] = -sin(angle/2.0);
	R[2] = sin(angle/2.0);
	R[3] = cos(angle / 2.0);

	operation(R, { qbit });
	return *this;
}

Quantum& Quantum::Rz(size_t qbit,double angle)
{
	std::vector<std::complex<double>> R(4);

	R[0] = std::complex < double >(cos(angle/2),sin(angle/2));
	R[1] = 0;
	R[2] = 0;
	R[3] = std::complex < double >(cos(angle / 2), sin(angle / 2));

	operation(R, { qbit });
	return *this;
}

Quantum& Quantum::P(size_t qbit,double angle)
{
	std::vector<std::complex<double>> P(4);

	P[0] = 1;
	P[1] = 0;
	P[2] = 0;
	P[3] = std::complex<double>(cos(angle), sin(angle));

	operation(P, { qbit });
	return *this;
}

Quantum& Quantum::CNOT(size_t controll, size_t controlled)
{
	std::vector<std::complex<double>> X(4);
	X[0] = 0;
	X[1] = 1;
	X[2] = 1;
	X[3] = 0;
	operation(X, { controll,controlled });

	return *this;
}

Quantum& Quantum::CH(size_t controll, size_t controlled)
{
	std::vector<std::complex<double>> H(4);
	H[0] = 1 / sqrt(2);
	H[1] = 1 / sqrt(2);
	H[2] = 1 / sqrt(2);
	H[3] = -1 / sqrt(2);
	operation(H, { controll,controlled });

	return *this;
}

Quantum& Quantum::CP(size_t controll, size_t controlled, double angle)
{
	std::vector<std::complex<double>> P(4);
	P[0] = 1;
	P[1] = 0;
	P[2] = 0;
	P[3] = std::complex<double>(cos(angle), sin(angle));
	operation(P, { controll,controlled });

	return *this;
}

void Quantum::operation(std::vector<std::complex<double>>& qop, std::vector<size_t> qbit)
{
	int mask = 0;
	int s = 0;
	if (qbit.size() == 1)
	{
		mask = 1<<qbit[0];
		s = mask;
	}

	if (qbit.size() == 2)
	{
		s = 1<<qbit[1];
		mask = (1 << qbit[0]) + s;
	}

	for (int i = 0; i < qbits.size(); ++i)
	{
		if ((i & mask) == mask)
		{
			std::complex <double> phi1 = qbits[i - s];
			std::complex<double> phi2 = qbits[i];
			qbits[i - s] = qop[0] * phi1 + qop[1] * phi2;
			qbits[i] = qop[2] * phi1 + qop[3] * phi2;
		}
	}
}



std::vector<int> Quantum::Measurment(size_t count_of_measurment)
{
	size_t states_count = std::pow(2, count);
	std::vector<int> result(states_count, 0);
	std::vector<double> distribution(states_count + 1);

	distribution[0] = 0.0;
	for (size_t i = 0; i < states_count; ++i) 
	{
		distribution[i + 1] = distribution[i] + std::abs(qbits[i])*std::abs(qbits[i]);
	}

	//for (size_t i = 0; i < distribution.size(); ++i)
		//std::cout << distribution[i] << ' ';
	//std::cout << endl;

	std::mt19937_64 gen(std::random_device{}());
	std::uniform_real_distribution<double> dis(0.0, 1.0);

	for (size_t i = 0; i < count_of_measurment; ++i) {
		double random_number = dis(gen);
		for (size_t j = 0; j < states_count; ++j) {
			if (random_number >= distribution[j] && random_number < distribution[j + 1]) {
				result[j]++;
				break;
			}
		}
	}

	return result;
}

std::ostream& operator<<(std::ostream& out, const Quantum& other)
{
    const double epsilon = 1e-10;
    out << "[";

    for (size_t i = 0; i < other.statescount(); ++i)
	{
        std::complex<double> val = other[i];
        double re = val.real();
        double im = val.imag();

        if (std::abs(re) < epsilon) re = 0.0;
        if (std::abs(im) < epsilon) im = 0.0;

        if (re == 0.0 && im == 0.0) 
		{
            out << "0";
        } 
        else 
		{
            if (re != 0.0) 
			{
                out << re;
            }

            if (im != 0.0) {
                if (re != 0.0 && im > 0) out << "+";
                
                if (im == 1.0) out << "i";
                else if (im == -1.0) out << "-i";
                else out << im << "i";
            }
        }

        if (i < other.statescount() - 1) {
            out << "; ";
        }
    }

    out << "]\n";
    return out;
}

double QuantumAlgorithms::getQFTPhase(size_t distance)
{
	return (std::acos(-1.0)) / (1 << (--distance));
}

Quantum& QuantumAlgorithms::QFT(Quantum& object,int first,int last)
{
	for (int i = last; i >= first; --i)
	{
		object.H(i);
		for (int j = i - 1; j >= first; --j)
			object.CP(j,i, getQFTPhase(i-j+1));
	}
	return object;
}

Quantum& QuantumAlgorithms::IQFT(Quantum& object, size_t first, size_t last)
{
	for (int i = first; i <= last; ++i)
	{
		for (int j = first; j < i; ++j)
		{
			object.CP(j, i, -getQFTPhase(i-j+1));
		}
		object.H(i);
	}
	return object;
}

Quantum &QuantumAlgorithms::Add(Quantum &object, size_t ffirst, size_t flast, size_t first, size_t last)
{
    if (ffirst-flast != first-last)
		throw std::system_error();

	int n = last-first+1;

	for (int i = n-1;i>=0;--i)
	{
		for (int j = i;j>=0;--j)
		{
			object.CP(first+j,ffirst+i,getQFTPhase(i-j+1));
		}
	}
	return object;
}

Quantum& QuantumAlgorithms::Add(Quantum& object,size_t first, size_t last, size_t num)
{
	int n = last - first + 1;
	for (int i = 0; i < n; ++i)
	{
		object.P(first+i,num * getQFTPhase(i + 1));
	}
	return object;
}

Quantum& QuantumAlgorithms::AddMod(Quantum& object,size_t first, size_t last, size_t add,size_t mod,size_t acille)
{
	Add(object,first,last,add);
	Sub(object,first,last,mod);
	IQFT(object,first,last);
	object.CNOT(acille,{last});
	QFT(object,first,last);
	Add(object,first,last,mod);
	Sub(object,first,last,add);
	IQFT(object,first,last);
	object.X(last);
	object.CNOT(acille,{last});
	object.X(last);
	QFT(object,first,last);
	Add(object,first,last,add);
	return object;
}

Quantum &QuantumAlgorithms::Sub(Quantum &object, size_t ffirst, size_t flast, size_t first, size_t last)
{
    if (ffirst-flast != first-last)
		throw std::system_error();

	int n = last-first+1;

	for (int i = n-1;i>=0;--i)
	{
		for (int j = i;j>=0;--j)
		{
			object.CP(first+j,ffirst+i,-getQFTPhase(i-j+1));
		}
	}
	return object;
}

Quantum& QuantumAlgorithms::Sub(Quantum& object,size_t first, size_t last, size_t num)
{
	int n = last - first + 1;
	for (int i = 0; i < n; ++i)
	{
		object.P(first + i,-static_cast<double>(num) * getQFTPhase(i + 1));
	}
	return object;
}