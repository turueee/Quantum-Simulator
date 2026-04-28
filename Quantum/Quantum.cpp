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
	operation(X, qbit, {});
	return *this;
}

Quantum& Quantum::Y(size_t qbit)
{
	std::vector<std::complex<double>> Y(4);

	Y[0] = 0;
	Y[1] = std::complex<double>(0.0, -1.0);
	Y[2] = std::complex<double>(0.0, 1.0);
	Y[3] = 0;
	operation(Y, qbit, {});
	return *this;
}

Quantum& Quantum::Z(size_t qbit)
{
	std::vector<std::complex<double>> Z(4);

	Z[0] = 1;
	Z[1] = 0;
	Z[2] = 0;
	Z[3] = -1;

	operation(Z, qbit, {});
	return *this;
}

Quantum& Quantum::H(size_t qbit)
{
	std::vector<std::complex<double>> H(4);

	H[0] = 1 / sqrt(2);
	H[1] = 1 / sqrt(2);
	H[2] = 1 / sqrt(2);
	H[3] = -1 / sqrt(2);

	operation(H, qbit, {});
	return *this;
}

Quantum& Quantum::S(size_t qbit)
{
	std::vector<std::complex<double>> S(4);

	S[0] = 1;
	S[1] = 0;
	S[2] = 0;
	S[3] = std::complex <double>(0.0,1.0) ;

	operation(S, qbit, {});
	return *this;
}

Quantum& Quantum::Rx(size_t qbit,double angle)
{
	std::vector<std::complex<double>> R(4);

	R[0] = cos(angle/2.0);
	R[1] = std::complex<double>(0.0, -sin(angle/2.0));
	R[2] = std::complex<double>(0.0, -sin(angle / 2.0));
	R[3] = cos(angle / 2.0);

	operation(R, qbit, {});
	return *this;
}

Quantum& Quantum::Ry(size_t qbit,double angle)
{
	std::vector<std::complex<double>> R(4);

	R[0] = cos(angle / 2.0);
	R[1] = -sin(angle/2.0);
	R[2] = sin(angle/2.0);
	R[3] = cos(angle / 2.0);

	operation(R, qbit, {});
	return *this;
}

Quantum& Quantum::Rz(size_t qbit,double angle)
{
	std::vector<std::complex<double>> R(4);

	R[0] = std::complex < double >(cos(angle/2),sin(angle/2));
	R[1] = 0;
	R[2] = 0;
	R[3] = std::complex < double >(cos(angle / 2), sin(angle / 2));

	operation(R, qbit, {});
	return *this;
}

Quantum& Quantum::P(size_t qbit,double angle)
{
	std::vector<std::complex<double>> P(4);

	P[0] = 1;
	P[1] = 0;
	P[2] = 0;
	P[3] = std::complex<double>(cos(angle), sin(angle));

	operation(P, qbit, {});
	return *this;
}

Quantum& Quantum::CNOT(size_t controlled, std::vector<size_t> controll)
{
	std::vector<std::complex<double>> X(4);
	X[0] = 0;
	X[1] = 1;
	X[2] = 1;
	X[3] = 0;
	operation(X, controlled, controll);

	return *this;
}

Quantum& Quantum::CH(size_t controlled, std::vector<size_t> controll)
{
	std::vector<std::complex<double>> H(4);
	H[0] = 1 / sqrt(2);
	H[1] = 1 / sqrt(2);
	H[2] = 1 / sqrt(2);
	H[3] = -1 / sqrt(2);
	operation(H, controlled, controll);

	return *this;
}

Quantum& Quantum::CP(size_t controlled, std::vector<size_t> controll, double angle)
{
	std::vector<std::complex<double>> P(4);
	P[0] = 1;
	P[1] = 0;
	P[2] = 0;
	P[3] = std::complex<double>(cos(angle), sin(angle));
	operation(P, controlled, controll);

	return *this;
}

Quantum &Quantum::SWAP(size_t first, size_t second)
{
    CNOT(second, {first});
    CNOT(first, {second});
    CNOT(second, {first});

	return *this;
}

Quantum &Quantum::CSWAP(size_t first, size_t second, size_t controll)
{
    CNOT(second, {first, controll});
    CNOT(first, {second, controll});
    CNOT(second, {first, controll});

	return *this;
}

void Quantum::operation(const std::vector<std::complex<double>>& qop, size_t target, const std::vector<size_t>& controls)
{
    size_t target_mask = (1ULL << target);
    
    size_t ctrl_mask = 0;
    #pragma omp parallel for num_threads(7)
    for (size_t c : controls) {
        ctrl_mask |= (1ULL << c);
    }
    #pragma omp parallel for num_threads(7)
    for (size_t i = 0; i < qbits.size(); ++i) 
	{
        if (((i & ctrl_mask) == ctrl_mask) && ((i & target_mask) == 0)) 
		{
            size_t i0 = i;
            size_t i1 = i | target_mask;

            std::complex<double> phi0 = qbits[i0];
            std::complex<double> phi1 = qbits[i1];

            qbits[i0] = qop[0] * phi0 + qop[1] * phi1;
            qbits[i1] = qop[2] * phi0 + qop[3] * phi1;
        }
    }
}

int Quantum::MeasureAndReset(size_t qbit)
{
    double p0 = 0.0;
    size_t mask = 1ULL << qbit;

    for (size_t i = 0; i < qbits.size(); ++i) {
        if ((i & mask) == 0) {
            p0 += std::norm(qbits[i]);
        }
    }

	static std::random_device rd;
	static std::mt19937_64 gen(rd());
	static std::uniform_real_distribution<double> dis(0.0, 1.0);

	int result = (dis(gen) > p0) ? 1 : 0;

    double norm_factor = std::sqrt(result == 0 ? p0 : (1.0 - p0));
    if (norm_factor < 1e-15) norm_factor = 1e-15;

    for (size_t i = 0; i < qbits.size(); ++i) {
        if (((i & mask) >> qbit) == result) {
            qbits[i] /= norm_factor;
        } else {
            qbits[i] = 0.0;
        }
    }
    if (result == 1) 
	{
        for (size_t i = 0; i < qbits.size(); ++i) 
		{
            if ((i & mask) != 0) 
			{
                qbits[i & ~mask] = qbits[i];
                qbits[i] = 0.0;
            }
        }
    }

    return result;
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
			object.CP(i, {static_cast<size_t>(j)}, getQFTPhase(i-j+1));
	}
	return object;
}

Quantum& QuantumAlgorithms::IQFT(Quantum& object, size_t first, size_t last)
{
	for (int i = first; i <= last; ++i)
	{
		for (int j = first; j < i; ++j)
		{
			object.CP(i, {static_cast<size_t>(j)}, -getQFTPhase(i-j+1));
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
			object.CP(ffirst+i, {first+j},getQFTPhase(i-j+1));
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

Quantum &QuantumAlgorithms::CAdd(Quantum &object, size_t first, size_t last, size_t num, std::vector<size_t> controll)
{
    int n = last - first + 1;
	for (int i = 0; i < n; ++i)
	{
		object.CP(first + i,controll ,num * getQFTPhase(i + 1));
	}
	return object;
}

Quantum& QuantumAlgorithms::CAddMod(Quantum& object,size_t first, size_t last, size_t add,size_t mod, size_t ancilla, std::vector<size_t> controll)
{
	CAdd(object, first, last, add, controll);
    Sub(object, first, last, mod);
    IQFT(object, first, last);
    object.CNOT(ancilla, {last});
    QFT(object, first, last);
    CAdd(object, first, last, mod, {ancilla});
    CSub(object, first, last, add, controll);
    IQFT(object, first, last);
    object.X(last);
    object.CNOT(ancilla, {last});
    object.X(last);
    QFT(object, first, last);
    CAdd(object, first, last, add, controll);
    
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
			object.CP(ffirst+i, {first+j}, -getQFTPhase(i-j+1));
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

Quantum &QuantumAlgorithms::CSub(Quantum &object, size_t first, size_t last, size_t num, std::vector<size_t> controll)
{
        int n = last - first + 1;
	for (int i = 0; i < n; ++i)
	{
		object.CP(first + i, controll , -static_cast<double>(num) * getQFTPhase(i + 1));
	}
	return object;
}

Quantum &QuantumAlgorithms::MulMod(Quantum &object, size_t first, size_t last, size_t xfirst, size_t xlast, size_t a, size_t N, size_t ancilla, size_t controll)
{
    size_t n = xlast - xfirst + 1;
    QFT(object, first, last);
    for (size_t i = 0; i < n; ++i)
    {
        size_t current_a = (static_cast<unsigned long long>(a) << i) % N;
        CAddMod(object, first, last, current_a, N, ancilla, {xfirst + i, controll});
    }
    IQFT(object, first, last);
    return object;
}

Quantum &QuantumAlgorithms::Ua_Gate(Quantum &object, size_t xfirst, size_t xlast, size_t afirst, size_t alast, size_t a, size_t N, size_t ancilla, size_t controll)
{
    size_t n = xlast - xfirst + 1;

    MulMod(object, afirst, alast, xfirst, xlast, a, N, ancilla, controll);
    CSWAP(object, xfirst, xlast, afirst, alast - 1, controll); 
    size_t a_inv = modInverse(a, N);
    MulMod(object, afirst, alast, xfirst, xlast, a_inv, N, ancilla, controll);
    return object;
}

Quantum &QuantumAlgorithms::CSWAP(Quantum& object, size_t first, size_t last, size_t afirst, size_t alast, size_t controll)
{
	size_t n = last - first + 1;
	for (size_t i = 0; i < n; ++i)
	{
		object.CSWAP(first + i, afirst + i, controll);
	}
	return object;
}

std::pair<size_t, size_t> QuantumAlgorithms::ShorAlgorithm(size_t number)
{
    auto stage1 = ShorAlgorithmFirstPhase(number);
    if (stage1.first != 0)
        return stage1;

    while (true) 
	{
        auto stage2 = ShorAlgorithmSecondPhase(number);
        size_t r = stage2.first;
        size_t a = stage2.second;

        auto stage3 = ShorAlgorithmThirdPhase(number, a, r);
        
        if (stage3.first != 0)
            return stage3;
    }
}

std::pair<size_t, size_t> QuantumAlgorithms::ShorAlgorithmFirstPhase(size_t number)
{
	if(number % 2 == 0)
		return {2,number/2};
	if(number % 3 == 0)
		return {3, number/3};
	if(number % 5 == 0)
		return {5, number/5};
	if(number % 7 == 0)
		return {7, number/7};
	return {0,0};
}

size_t QuantumAlgorithms::findPeriodByPeakDistance(const std::vector<int>& histogram, size_t Q) {
    size_t peak1 = 0, peak2 = 0;
    int val1 = 0, val2 = 0;

    for (size_t i = 1; i < histogram.size(); ++i) {
        if (histogram[i] > val1) {
            val1 = histogram[i];
            peak1 = i;
        }
    }
    for (size_t i = 1; i < histogram.size(); ++i) {
        if (std::abs((int)i - (int)peak1) > (int)(Q * 0.05)) { 
            if (histogram[i] > val2) {
                val2 = histogram[i];
                peak2 = i;
            }
        }
    }
    if (val1 == 0 || val2 == 0) return 0;
    size_t delta_y = (peak1 > peak2) ? (peak1 - peak2) : (peak2 - peak1);
    return static_cast<size_t>(std::round(static_cast<double>(Q) / delta_y));
}

std::pair<size_t, size_t> QuantumAlgorithms::ShorAlgorithmSecondPhase(size_t number) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(2, number - 1);
    size_t a = dist(gen);

    size_t g = std::gcd(a, number);
    if (g > 1) return {0, a};

    size_t n = 64 - __builtin_clzll(static_cast<uint64_t>(number));
    size_t precision = 2 * n;
    size_t Q = 1ULL << precision;

    size_t total_qbits = precision + 2 * n + 2; 
    Quantum object(total_qbits);

    size_t c_first = 0;   
    size_t x_first = precision;              
    size_t x_last = precision + n - 1;
    size_t a_first = precision + n;        
    size_t a_last = precision + 2 * n;
    size_t ancilla = precision + 2 * n + 1;

    object.X(x_first); 

    for (size_t i = 0; i < precision; ++i) {
        object.H(c_first + i);
    }

    for (size_t k = 0; k < precision; ++k) {
        size_t power_a = modPow(a, 1ULL << k, number);
        if (power_a != 1) 
		{
            Ua_Gate(object, x_first, x_last, a_first, a_last, power_a, number, ancilla, c_first + k);
        }
    }

    IQFT(object, c_first, c_first + precision - 1);
	size_t shots = std::max((size_t)1000, Q / 4);
    std::vector<int> samples = object.Measurment(shots);

    std::vector<int> phase_histogram(Q, 0);
    for (size_t i = 0; i < samples.size(); ++i) {
        if (samples[i] > 0) {
            size_t y = i & (Q - 1);
            phase_histogram[y] += samples[i];
        }
    }

    size_t r = findPeriodByPeakDistance(phase_histogram, Q);

    return {r, a};
}

std::pair<size_t, size_t> QuantumAlgorithms::ShorAlgorithmThirdPhase(size_t number, size_t a, size_t r) 
{
    if (r == 0) {
        size_t g = std::gcd(a, number);
        if (g > 1) return {g, number / g};
        return {0, 0};
    }

    if (r % 2 != 0) 
        return {0, 0};

    size_t val = modPow(a, r / 2, number);

    if (val == 1 || val == number - 1) {
        return {0, 0};
    }

    size_t p = std::gcd(val - 1, number);
    size_t q = std::gcd(val + 1, number);

    if (p * q == number && p > 1) 
	{
        return {p, q};
    }

    return {0, 0};
}
size_t QuantumAlgorithms::modPow(size_t base, size_t exp, size_t mod) 
{
    size_t res = 1;
    base %= mod;
    while (exp > 0) 
	{
        if (exp % 2 == 1) 
            res = static_cast<size_t>((static_cast<unsigned __int128>(res) * base) % mod);
        base = static_cast<size_t>((static_cast<unsigned __int128>(base) * base) % mod);
        exp /= 2;
    }
    return res;
}

size_t QuantumAlgorithms::findPeriodFromMeasurement(size_t y, size_t Q, size_t a, size_t N) 
{
    if (y == 0) return 0; 

    std::vector<size_t> a_vals;
    size_t num = y;
    size_t den = Q;
    
    
    for (int i = 0; i < 40; ++i) 
	{ 
        if (den == 0) break;
        a_vals.push_back(num / den);
        size_t rem = num % den;
        num = den;
        den = rem;
    }
    
    size_t p_prev2 = 0, p_prev1 = 1;
    size_t q_prev2 = 1, q_prev1 = 0;
    
    for (size_t a_i : a_vals) 
	{
        size_t p_curr = a_i * p_prev1 + p_prev2;
        size_t q_curr = a_i * q_prev1 + q_prev2;
        
        if (q_curr > 0 && q_curr < N) 
		{
            if (modPow(a, q_curr, N) == 1) {
                return q_curr;
            }
        }
        p_prev2 = p_prev1; p_prev1 = p_curr;
        q_prev2 = q_prev1; q_prev1 = q_curr;
    }
    
    return 0;
}

size_t QuantumAlgorithms::modInverse(size_t a, size_t N) 
{
    long long m0 = N, t, q;
    long long x0 = 0, x1 = 1;

    if (N == 1) return 0;

    long long a_long = a % N;

    while (a_long > 1) 
	{
        q = a_long / m0;
        t = m0;

        m0 = a_long % m0, a_long = t;
        t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0) x1 += N;

    return static_cast<size_t>((N - x1));
}