#pragma once

#include <iostream>
#include <random>
#include "TError.h"
#include "TVector.h"

using namespace std;

template<class T>
class TMatrix {
protected:
  int n;
  int m;
  T** matrix;
public:
  TMatrix();
  TMatrix(int n_, int m_);
  TMatrix(const TMatrix& table);
  TMatrix(TMatrix&& table);
  ~TMatrix();

  int GetN();
  int GetM();
  void GetMatrix(T*** array);

  void SetN(int n_);
  void SetM(int m_);
  void SetMatrix(T**array);

  
  /// 2 level
  TVector<T> operator*(const TVector<T>& table);
  TVector<T> Gauss(TVector<T>& table);
 
  /// 3 level
  TMatrix<T> Transposition();
  TMatrix<T> Minor(int string, int column);
  TMatrix<T> Attached();
  TMatrix<T> Inverse();
  T Determinant();
  int CountOfIncludes(T num);
  TMatrix<T> IndexesOfIncludes(T num);
  TMatrix<T> Pow(int st);

  TMatrix operator+(const TMatrix<T>& table);
  TMatrix operator-(const TMatrix<T>& table);
  TMatrix operator*(const TMatrix<T>& table);
  TMatrix operator/(const TMatrix<T>& table);
  TMatrix operator*(T num);
  TMatrix operator/(T num);
  void operator=(const TMatrix<T>& table);
  void operator=(TMatrix<T>&& table);
  bool operator==(const TMatrix<T>& table);
  void Rand(int min,int max);
  void Save();
  T*& operator[](int index);

  template <class O>
  friend ostream& operator<<(ostream& o, TMatrix<O>& t);
  template <class I>
  friend istream& operator>>(istream& i, TMatrix<I>& t);
};


template<class T>
inline TMatrix<T>::TMatrix()
{
  n = 0;
  m = 0;
  matrix = nullptr;
}


template<class T>
inline TMatrix<T>::TMatrix(int n_, int m_)
{
  if (n_ < 0)
    throw TError("n_ < 0", __func__, __FILE__, __LINE__);
  else if (m_ < 0)
    throw TError("m_ < 0", __func__, __FILE__, __LINE__);
  else if (n_ == 0 || m_ == 0)
  {
    matrix = nullptr;
    n = 0;
    m = 0;
  }
  else
  {
    n = n_;
    m = m_;
    matrix = new T * [n];
    for (int i = 0; i < n; ++i)
      matrix[i] = new T[m]{0};
  }
}


template<class T>
inline TMatrix<T>::TMatrix(const TMatrix& table)
{
  n = table.n;
  m = table.m;
  if (n == 0 || m == 0)
    matrix = nullptr;
  else
  {
    matrix = new T * [n];
    for (int i = 0; i < n; ++i)
    {
      matrix[i] = new T[m];
      for (int j = 0; j < m; ++j)
      {
        matrix[i][j] = table.matrix[i][j];
      }
    }
  }
}


template<class T>
inline TMatrix<T>::TMatrix(TMatrix&& table)
{
  n = table.n;
  m = table.m;
  matrix = table.matrix;
  table.n = 0; 
  table.m = 0;
  table.matrix = nullptr;
}


template<class T>
inline TMatrix<T>::~TMatrix()
{
  if (matrix != nullptr)
  {
    for (int i = 0; i < n; ++i)
      delete[] matrix[i];
    delete[] matrix;
  }
}


template<class T>
inline int TMatrix<T>::GetN()
{
  return n;
}


template<class T>
inline int TMatrix<T>::GetM()
{
  return m;
}


template<class T>
inline void TMatrix<T>::GetMatrix(T*** array)
{
  if (matrix == nullptr)
  {
    (*array) == nullptr;
  }
  else
  {
    (*array) = new T * [n];
    for (int i = 0; i < n; ++i)
    {
      (*array)[i] = new T[m];
    }
    for (int i = 0; i < n; ++i)
    {
      for (int j = 0; j < m; ++j)
        (*array)[i][j] = matrix[i][j];
    }
  }
}


template<class T>
inline void TMatrix<T>::SetN(int n_)
{
  if (n_ < 0)
    throw TError("n_ < 0", __func__, __FILE__, __LINE__);
  else if (n_ == 0)
  {
    n = 0;
    m = 0;
    matrix = nullptr;
  }
  else if (n == n_)
    return;
  else
  {
    T** array;
    this->GetMatrix(&array);
    for (int i = 0; i < n; ++i)
      delete[] matrix[i];
    delete[] matrix;
    if (n_ < n)
    {
      n = n_;
      matrix = new T * [n];
      for (int i = 0; i < n; ++i)
        matrix[i] = new T[m];
      for (int i = 0; i < n; ++i)
      {
        for (int j = 0; j < m; ++j)
          matrix[i][j] = array[i][j];
        delete[] array[i];
      }
      delete[] array;
    }
    else
    {
      matrix = new T * [n_];
      for (int i = 0; i < n_; ++i)
        matrix[i] = new T[m];
      for (int i = 0; i < n; ++i)
      {
        for (int j = 0; j < m; ++j)
          matrix[i][j] = array[i][j];
        delete[] array[i];
      }
      delete[] array;
      for (int i = n; i < n_; ++i)
      {
        for (int j = 0; j < m; ++j)
          matrix[i][j] = 0;
      }
      n = n_;
    }
  }
}


template<class T>
inline void TMatrix<T>::SetM(int m_)
{
  if (m == m_)
    return;
  else if (m_ < 0)
    throw TError("m_ < 0", __func__, __FILE__, __LINE__);
  else if (m_ == 0)
  {
    n = 0;
    m = 0;
    matrix = nullptr;
  }
  else if (matrix == nullptr)
  {
    m = m_;
    n = 1;
    matrix = new T*[n];
    for (int i = 0; i < n; ++i)
    {
      matrix[i] = new T[m]{0};
    }
  }
  else
  {
    T* vector;
    if (m_ < m)
    {
      for (int i = 0; i < n; ++i)
      {
        m = m_;
        vector = new T[m];
        for (int j = 0; j < m; ++j)
        {
          vector[j] = matrix[i][j];
        }
        delete[] matrix[i];
        matrix[i] = new T[m];
        for (int j = 0; j < m; ++j)
        {
          matrix[i][j] = vector[j];
        }
        delete[] vector;
      }
    }
    else
    {
      for (int i = 0; i < n; ++i)
      {
        vector = new T[m];
        for (int j = 0; j < m; ++j)
        {
          vector[j] = matrix[i][j];
        }
        delete[] matrix[i];
        matrix[i] = new T[m_];
        for (int j = 0; j < m; ++j)
        {
          matrix[i][j] = vector[j];
        }
        for (int j = m; j < m_; ++j)
        {
          matrix[i][j] = 0;
        }
        delete[] vector;
      }
      m = m_;
    }
  }
}


template<class T>
inline void TMatrix<T>::SetMatrix(T** array)
{
  if (matrix == nullptr)
    return;
  else
  {
    try
    {
      T test = array[n - 1][m - 1];
    }
    catch (...)
    {
      throw TError("size error", __func__, __FILE__, __LINE__);
    }
    for (int i = 0; i < n; ++i)
    {
      for (int j = 0; j < m; ++j)
      {
        matrix[i][j] = array[i][j];
      }
    }
  }
}


template<class T>
inline TVector<T> TMatrix<T>::operator*(const TVector<T>& line)
{
  TVector<T>c(line);
  int l = c.GetLen();
  if (m != l)
    throw TError("m != line.len", __func__, __FILE__, __LINE__);
  else if (n == 0 || l == 0)
    throw TError("matrix == nullptr || line.vector==nullptr", __func__, __FILE__, __LINE__);
  else
  {
    TVector<T> res(n);
    for (int i = 0; i < n; ++i)
    {
      for (int j = 0; j < m; ++j)
        res[i] += matrix[i][j]*line[j];
    }
    return TVector<T>(res);
  }
}

template<class T>
inline TMatrix<T> TMatrix<T>::Transposition()
{
  if (matrix == nullptr)
    throw TError("matrix == nullptr", __func__, __FILE__, __LINE__);
  TMatrix<T> table(m,n);
  for (int j = 0; j < m; ++j)
  {
    for (int i = 0; i < n; ++i)
    {
      table.matrix[j][i] = matrix[i][j];
    }
  }
  return TMatrix<T>(table);
}


template<class T>
inline TMatrix<T> TMatrix<T>::Minor(int string, int column)
{
  if (n != m)
    throw TError("n!=m", __func__, __FILE__, __LINE__);
  if (matrix == nullptr)
    throw TError("matrix == nullptr", __func__, __FILE__, __LINE__);
  TMatrix<T> cp(n - 1, m - 1);
  int newi = 0;
  for (int i = 0; i < n; ++i)
  {
    if (i != column)
    {
      int newj = 0;
      for (int j = 0; j < m; ++j)
      {
        if (j != string)
        {
          cp.matrix[newi][newj] = matrix[i][j];
          newj++;
        }
      }
      newi++;
    }
  }
  return TMatrix<T>(cp);
}


template<class T>
inline TMatrix<T> TMatrix<T>::Attached()
{
  if (matrix == nullptr)
    throw TError("matrix == nullptr", __func__, __FILE__, __LINE__);
  if (n != m || n==1)
    throw TError("n != m || n == 1", __func__, __FILE__, __LINE__);
  else
  {
    TMatrix<T> cp(n, m);
    for (int i = 0; i < n; ++i)
    {
      for (int j = 0; j < m; ++j)
      {
        TMatrix<T> d = this->Minor(i, j);
        cp.matrix[j][i] = d.Determinant() * pow(-1, i + j);
      }
    }
    return TMatrix <T> (cp);
  }
}


template<class T>
inline TMatrix<T> TMatrix<T>::Inverse()
{
  if (matrix == nullptr)
    throw TError("matrix == nullptr", __func__, __FILE__, __LINE__);
  if (n != m)
    throw TError("n != m", __func__, __FILE__, __LINE__);
  else if (this->Determinant() == 0)
    throw TError("Determinant == 0", __func__, __FILE__, __LINE__);
  else if (n == 1)
  {
    TMatrix<T> cp;
    cp.matrix[0][0] = 1 / matrix[0][0];
    return cp;
  }
  else if (n>=2)
  {
    TMatrix<T> t(*this),e(t.GetN(),t.GetN());
    for (int i = 0; i < n; ++i)
      e[i][i] = 1;

    for (int i = 0; i < n; ++i)
    {
      for (int j = 0; j < n; ++j)
      {
        if (i != j)
        {
          T mul = t.matrix[j][i];
          for (int k = 0; k < n; ++k)
          {
            if (t.matrix[j][k] != 0)
            {
              e.matrix[j][k] = e.matrix[j][k] * t.matrix[i][i] - e.matrix[i][k] * mul;
              t.matrix[j][k] = t.matrix[j][k] * t.matrix[i][i] - t.matrix[i][k] * mul;
            }
          }
        }
      }
    }
    for (int i = 0; i < n; ++i)
    {
      for (int j = 0; j < n; ++j)
        e.matrix[i][j] /= t.matrix[i][i];
    }
    return TMatrix<T>(e);
  }
}

template<class T>
inline TVector<T> TMatrix<T>::Gauss(TVector<T>& table)
{
  if (matrix==nullptr || table.GetLen() == 0)
    throw TError("matrix==nullptr || table.vector == nullptr", __func__, __FILE__, __LINE__);
  if (n != m || n != table.GetLen())
    throw TError("n != m", __func__, __FILE__, __LINE__);
  else if (this->Determinant()==0)
    throw TError("det == 0", __func__, __FILE__, __LINE__);
  else
  {
    TMatrix<T> t(*this);
    TVector<T> res(table);
    for (int i = 0; i < n; ++i)
    {
      for (int j = 0; j < n; ++j)
      {
        if (i != j)
        {
          T mul = t.matrix[j][i];
          res[j] = res[j] * t.matrix[i][i] - res[i] * mul;
          for (int k = 0; k < n; ++k)
          {
            t.matrix[j][k] = t.matrix[j][k] * t.matrix[i][i] - t.matrix[i][k] * mul;
          }
        }
      }
    }
    for (int i = 0; i < n; ++i)
      res[i] = res[i] / t.matrix[i][i];
    return TVector<T>(res);
  }
}


template<class T>
inline T TMatrix<T>::Determinant()
{
  if (matrix == nullptr)
    throw TError("matrix == nullptr", __func__, __FILE__, __LINE__);
  if (n != m)
    throw TError("n != m", __func__, __FILE__, __LINE__);
  if (n == 1)
    return matrix[0][0];
  else if (n == 2)
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
  else
  {
    TMatrix<T> t(*this);
    for (int i = 0; i < n; ++i)
    {
      for (int j = i+1; j < n; ++j)
      {
        T mul = t.matrix[j][i];
        for (int k = 0; k < n; ++k)
        {
          if (t.matrix[j][k] != 0)
            t.matrix[j][k] = t.matrix[j][k] * t.matrix[i][i] - t.matrix[i][k] * mul;
        }
      }
    }
    T det = 1;
    for (int i = 0; i < n;++i)
      det *= t.matrix[i][i];
    return det;
  }
}


template<class T>
inline int TMatrix<T>::CountOfIncludes(T num)
{
  if (matrix == nullptr)
    throw TError("matrix == nullptr", __func__, __FILE__, __LINE__);
  int count = 0;
  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < m; ++j)
    {
      if (matrix[i][j] == num)
        count++;
    }
  }
  return count;
}


template<class T>
inline TMatrix<T> TMatrix<T>::IndexesOfIncludes(T num)
{
  if (matrix == nullptr)
    throw TError("matrix == nullptr", __func__, __FILE__, __LINE__);
  int count = 0;
  TMatrix<T> res(this->CountOfIncludes(num),2);
  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < m; ++j)
    {
      if (matrix[i][j] == num)
      {
        res.matrix[count][0] = T(j);
        res.matrix[count][1] = T(i);
        count++;
      }
    }
  }
  return res;
}


template<class T>
inline TMatrix<T> TMatrix<T>::Pow(int st)
{
  if (matrix == nullptr)
    throw TError("matrix == nullptr", __func__, __FILE__, __LINE__);
  else if (n != m)
    throw TError("n != m", __func__, __FILE__, __LINE__);
  else if (st == 0)
  {
    TMatrix<T> a(n, n);
    for (int i = 0; i < n; ++i)
      a[i][i] == 1;
    return TMatrix<T>(a);
  }
  else if (st > 0)
  {
    TMatrix<T> a(*this),res(*this);
    for (int i = 1; i < st; ++i)
      res = res * a;
    return TMatrix < T>(res);
  }
  else
  {
    TMatrix<T> a(*this), res(*this);
    a = a.Inverse();
    res = a;
    for (int i = 1; i < st; ++i)
      res = res * a;
    return TMatrix < T> (res);
  }
}


template<class T>
inline TMatrix<T> TMatrix<T>::operator+(const TMatrix<T>& table)
{
  if (matrix == nullptr)
    throw TError("matrix == nullptr", __func__, __FILE__, __LINE__);
  else if (table.matrix == nullptr)
    throw TError("table.matrix == nullptr", __func__, __FILE__, __LINE__);
  else if (n != table.n || m != table.m)
    throw TError("n != table.n || m != table.m", __func__, __FILE__, __LINE__);
  else
  {
    TMatrix<T> cp(n, m);
    for (int i = 0; i < n; ++i)
    {
      for (int j = 0; j < m; ++j)
        cp.matrix[i][j] = matrix[i][j] + table.matrix[i][j];
    }
    return TMatrix<T>(cp);
  }  
}


template<class T>
inline TMatrix<T> TMatrix<T>::operator-(const TMatrix<T>& table)
{
  if (matrix == nullptr)
    throw TError("matrix == nullptr", __func__, __FILE__, __LINE__);
  else if (table.matrix == nullptr)
    throw TError("table.matrix == nullptr", __func__, __FILE__, __LINE__);
  else if (n != table.n || m != table.m)
    throw TError("n != table.n || m != table.m", __func__, __FILE__, __LINE__);
  else
  {
    TMatrix<T> cp(n, m);
    for (int i = 0; i < n; ++i)
    {
      for (int j = 0; j < m; ++j)
        cp.matrix[i][j] = matrix[i][j] - table.matrix[i][j];
    }
    return TMatrix<T>(cp);
  }
}

template<class T>
inline TMatrix<T> TMatrix<T>::operator*(const TMatrix& table)
{
  if (matrix == nullptr)
    throw TError("matrix == nullptr", __func__, __FILE__, __LINE__);
  else if (table.matrix == nullptr)
    throw TError("table.matrix == nullptr", __func__, __FILE__, __LINE__);
  else if (m!=table.n)
    throw TError("m!=table.n", __func__, __FILE__, __LINE__);
  else
  {
    TMatrix<T> res(n,table.m);
    for (int i = 0;i<res.n;++i)
    {
      for (int j = 0; j < res.m; ++j)
      {
        res.matrix[i][j] = 0;
        for (int k = 0; k < m; ++k)
          res.matrix[i][j] += matrix[i][k] * table.matrix[k][j];
      }
    }
    return TMatrix < T>(res);
  }
}

template<class T>
inline TMatrix<T> TMatrix<T>::operator/(const TMatrix<T>& table)
{
  TMatrix<T> r(table), l(*this);
  return TMatrix<T>(l*r.Inverse());
}


template<class T>
inline TMatrix<T> TMatrix<T>::operator*(T num)
{
  if (matrix == nullptr)
    throw TError("matrix == nullptr", __func__, __FILE__, __LINE__);
  TMatrix<T> res(n,m);
  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < m; ++j)
      res.matrix[i][j] = num * matrix[i][j];
  }
  return TMatrix<T>(res);
}


template<class T>
inline TMatrix<T> TMatrix<T>::operator/(T num)
{
  if (matrix == nullptr)
    throw TError("matrix == nullptr", __func__, __FILE__, __LINE__);
  if(num==(T)0)
    throw TError("num==0", __func__, __FILE__, __LINE__);
  else
  {
    TMatrix<T> res(n, m);
    for (int i = 0; i < n; ++i)
    {
      for (int j = 0; j < m; ++j)
        res.matrix[i][j] = matrix[i][j] / num;
    }
    return TMatrix<T>(res);
  }
}


template<class T>
inline void TMatrix<T>::operator=(const TMatrix<T>& table)
{
  if (this == &table)
    return;

  if (table.m == 0)
  {
    matrix = nullptr;
    n = 0;
    m = 0;
  }
  else
  {
    n = table.n;
    m = table.m;
    matrix = new T * [n];
    for (int i = 0; i < n; ++i)
    {
      matrix[i] = new T[m]{ 0 };
      for (int j = 0; j < m; ++j)
        matrix[i][j] = table.matrix[i][j];
    }
  }
}

template<class T>
inline void TMatrix<T>::operator=(TMatrix<T>&& table)
{
  if (this == &table)
    return;

  if (matrix != nullptr)
  {
    for (int i = 0; i < n; ++i)
      delete[]matrix[i];
    delete[] matrix;
  }

  matrix = table.matrix;
  n = table.n;
  m = table.m;
  table.matrix = nullptr;
  table.m = 0;
  table.n = 0;
}


template<class T>
inline bool TMatrix<T>::operator==(const TMatrix& table)
{
  if (matrix == nullptr && table.matrix == nullptr)
    return true;
  else if (matrix == nullptr)
    throw TError("matrix == nullptr", __func__, __FILE__, __LINE__);
  else if (table.matrix == nullptr)
    throw TError("table.matrix == nullptr", __func__, __FILE__, __LINE__);
  else if (n != table.n || m != table.m)
    return false;
  else
  {
    for (int i = 0; i < n; ++i)
    {
      for (int j = 0; j < m; ++j)
      {
        if (matrix[i][j] != table.matrix[i][j])
          return false;
      }
    }
    return true;
  }
}

template<class T>
inline void TMatrix<T>::Rand(int min,int max)
{
  static std::random_device rd;
  static std::mt19937 gen(rd());

  std::uniform_int_distribution<int> dist(min, max);
  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < m; ++j)
      matrix[i][j] = dist(gen);
  }
}

template<class T>
inline void TMatrix<T>::Save()
{
  FILE* file_of_numbers;
  file_of_numbers = fopen("result_massive.txt", "w");
  if (file_of_numbers != NULL)
  {
    fprintf(file_of_numbers, "Matrix %d*%d:\n",n,m);
  }
  else
    printf("FILE ERROR!!!");
  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < m; ++j)
    {
      if (file_of_numbers != NULL)
      {
        fprintf(file_of_numbers, "%lf\t", matrix[i][j]);
      }
      else
        printf("FILE ERROR!!!");
    }
    if (file_of_numbers != NULL)
    {
      fprintf(file_of_numbers, "\n");
    }
    else
      printf("FILE ERROR!!!");
  }
  fclose(file_of_numbers);
}


template<class T>
inline T*& TMatrix<T>::operator[](int index)
{
  if (matrix == nullptr)
    throw TError("matrix == nullptr", __func__, __FILE__, __LINE__);
  if (index >= n)
    throw TError("index >= n", __func__, __FILE__, __LINE__);
  return matrix[index];
}


template<typename O>
inline ostream& operator<<(ostream& o, TMatrix<O>& t)
{
  if (t.matrix == nullptr)
  {
    o << "Size: " << 0 << " * " << 0 << ".\n"<<"[]";
  }
  else
  {
    o << "Size: " << t.n << " * " << t.m << ".\n";
    for (int i = 0; i < t.n; ++i)
    {
      o << "\t";
      for (int j = 0; j < t.m; ++j)
      {
        o << t.matrix[i][j] << "\t";
      }
      o << endl;
    }
  }
  return o;
}


template <typename I>
inline istream& operator>>(istream& i, TMatrix<I>& t)
{
  cout << "Enter the count of strings: ";
  cin >> t.n;
  cout << "Enter the count of columns: ";
  cin >> t.m;
  if (t.m<0 || t.n)
  if (t.m == 0 || t.n == 0)
    t.matrix = nullptr;
  else
  {
    t.matrix = new I * [t.n];
    for (int i = 0; i < t.n; ++i)
    {
      t.matrix[i] = new I[t.m];
      for (int j = 0; j < t.m; ++j)
      {
        cout << "matrix[" << i << "][" << j << "] = ";
        cin >> t.matrix[i][j];
      }
    }
  }
  return i;
}