#pragma once

#include <iostream>
#include <random>
#include "TError.h"

using namespace std;

template <class T>
class TVectorIterator;

template<class T>
class TVector {
protected:
  int len;
  T* vector;
public:
  TVector();
  TVector(int len_);
  TVector(const TVector& line);
  TVector(TVector&& line);
  ~TVector();

  int GetLen();
  void GetVector(T** array);

  void SetLen(int n_);
  void SetVector(T* array,int len_);

  TVector operator+(const TVector<T>& line);
  TVector operator-(const TVector<T>& line);
  T operator*(const TVector<T>& line);
  TVector operator*(T num);
  TVector operator/(T num);

  TVector& operator=(const TVector<T>& line);
  TVector& operator=(TVector<T>&& line);
  bool operator==(const TVector<T>& line);

  T& operator[](int index) const;

  TVector BublleSort();
  TVector QuickSort(int left,int right);
  TVector InsertionSort();

  TVector<T> Normalisation();
  T FirstNorm();
  T SecondNorm();
  T InfinityNorm();
  T HelderNorm();
  void Rand(int min,int max);

  void Save();

  TVectorIterator<T> begin();
  TVectorIterator<T> end();


  template <class O>
  friend ostream& operator<<(ostream& o, TVector<O>& t);
  template <class I>
  friend istream& operator>>(istream& i, TVector<I>& t);
};


template<class T>
class TVectorIterator
{
protected:
  TVector<T>& p;
  int index;
public:
  TVectorIterator(TVector<T>& vector, int index_ = 0);
  T& operator*();
  TVectorIterator<T>& operator++();
  TVectorIterator<T>& operator++(int);

  bool operator != (const TVectorIterator<T>& p);
};

template<class T>
inline TVector<T>::TVector()
{
  len = 0;
  vector = nullptr;
}

template<class T>
inline TVector<T>::TVector(int len_)
{
  if (len_ < 0)
    throw TError("len_ < 0", __func__, __FILE__, __LINE__);
  else if (len = 0)
    vector = nullptr;
  else
  {
    len = len_;
    vector = new T[len]{ 0 };
  }
}

template<class T>
inline TVector<T>::TVector(const TVector& line)
{
  len = line.len;
  if (len == 0)
    vector = nullptr;
  else
  {
    vector = new T[len];
    for (int i = 0; i < len; ++i)
      vector[i] = line.vector[i];
  }
}

template<class T>
inline TVector<T>::TVector(TVector&& line)
{
  vector = line.vector;
  len = line.len;

  line.len = 0;
  line.vector = nullptr;
}

template<class T>
inline TVector<T>::~TVector()
{
  if (len != 0)
    delete[] vector;
  vector = nullptr;
  len = 0;
}

template<class T>
inline int TVector<T>::GetLen()
{
  return len;
}

template<class T>
inline void TVector<T>::GetVector(T** array)
{
  (*array) = new T[len];
  for (int i = 0; i < len; ++i)
    *array = vector[i];
}

template<class T>
inline void TVector<T>::SetLen(int len_)
{
  if (len_ < 0)
    throw TError("len_ < 0", __func__, __FILE__, __LINE__);
  else if (len == len_)
    return;
  else if (len_ == 0)
  {
    len = len_;
    delete[] vector;
  }
  else if (len == 0)
  {
    len = len_;
    vector = new T[len]{ 0 };
  }
  else if (len_ < len)
  {
    T* reserv = new T[len_];
    for (int i = 0; i < len_; ++i)
      reserv[i] = vector[i];
    delete[] vector;
    len = len_;
    vector = new T[len_];
    for (int i = 0; i < len_; ++i)
      vector[i] = reserv[i];
    delete[] reserv;
  }
  else
  {
    T* reserv = new T[len];
    for (int i = 0; i < len; ++i)
      reserv[i] = vector[i];
    delete[] vector;
    vector = new T[len_]{0};
    for (int i = 0; i < len; ++i)
      vector[i] = reserv[i];
    len = len_;
    delete[] reserv;
  }
}

template<class T>
inline void TVector<T>::SetVector(T* array, int len_)
{
  if (len_ < 0)
    throw TError("len_ < 0", __func__, __FILE__, __LINE__)
  else if (len_ == 0)
    return;
  else
  {
    for (int i = 0; i < min(len, len_); i++)
      vector[i] = array[i];
  }
}

template<class T>
inline TVector<T> TVector<T>::operator+(const TVector<T>& line)
{
  if (len != line.len)
    throw TError("len != line.len", __func__, __FILE__, __LINE__);
  else if (len == 0)
  {
    return TVector();
  }
  else
  {
    TVector<T> res(len);
    for (int i = 0; i < len; ++i)
      res.vector[i] = vector[i] + line.vector[i];
    return res;
  }
}

template<class T>
inline TVector<T> TVector<T>::operator-(const TVector<T>& line)
{
  if (len != line.len)
    throw TError("len != line.len", __func__, __FILE__, __LINE__);
  else if (len == 0)
  {
    return TVector();
  }
  else
  {
    TVector<T> res(len);
    for (int i = 0; i < len; ++i)
      res.vector[i] = vector[i] - line.vector[i];
    return res;
  }
}

template<class T>
inline T TVector<T>::operator*(const TVector<T>& line)
{
  if (len != line.len)
    throw TError("len != line.len", __func__, __FILE__, __LINE__);
  else if (len == 0 || line.len ==0)
  {
    throw TError("len == 0 || line.len == 0", __func__, __FILE__, __LINE__);
  }
  else
  {
    T res = 0;
    for (int i = 0; i < len; ++i)
      res += vector[i] * line.vector[i];
    return res;
  }
}

template<class T>
inline TVector<T> TVector<T>::operator*(T num)
{
  if (vector == nullptr)
  {
    return TVector();
  }
  else
  {
    TVector<T> res(len);
    for (int i = 0; i < len; ++i)
      res.vector[i] = vector[i] * num;
    return res;
  }
}

template<class T>
inline TVector<T> TVector<T>::operator/(T num)
{
  if (num==0)
    throw TError("num == 0", __func__, __FILE__, __LINE__);
  if (vector == nullptr)
  {
    return TVector();
  }
  else
  {
    TVector<T> res(len);
    for (int i = 0; i < len; ++i)
      res.vector[i] = vector[i] / num;
    return res;
  }
}

template<class T>
inline TVector<T>& TVector<T>::operator=(const TVector<T>& obj)
{
  if (this == &obj)
    return *this;

  if (len != obj.len)
  {
    delete[] vector;
    vector = new T[obj.len];
  }
  len = obj.len;
  for (int i = 0; i < len; i++)
    vector[i] = obj.vector[i];

  return *this;
}

template<class T>
inline TVector<T>& TVector<T>::operator=(TVector<T>&& obj)
{
  if (this == &obj)
    return *this;

  if (vector != nullptr)
    delete[] vector;

  vector = obj.vector;
  len = obj.len;
  obj.vector = nullptr;
  obj.len = 0;
  return *this;
}

template<class T>
inline bool TVector<T>::operator==(const TVector<T>& line)
{
  if (len != line.len)
    return false;
  else if (len == 0)
  {
    return true;
  }
  else
  {
    for (int i = 0; i < len; ++i)
    {
      if (vector[i] != line.vector[i])
        return false;
    }
    return true;
  }
}

template<class T>
inline T& TVector<T>::operator[](int index) const
{
  if (vector == nullptr)
    throw TError("vector==nullptr", __func__, __FILE__, __LINE__);
  else if (index >= len)
    throw TError("index >= len", __func__, __FILE__, __LINE__);
  else
    return vector[index];
}

template<class T>
inline TVector<T> TVector<T>::BublleSort()
{
  if (len == 0)
    throw TError("len == 0", __func__, __FILE__, __LINE__);
  T rezerv;
  TVector<T> res(*this);
  for (int i = 0; i < len; ++i)
  {
    for (int j = 0; j < (len - 1); ++j)
    {
      if (res[j] > res[j + 1])
      {
        rezerv = res[j];
        res[j] = res[j + 1];
        res[j + 1] = rezerv;
      }
    }
  }
  return res;
}

template<class T>
inline TVector<T> TVector<T>::QuickSort(int left, int right)
{
  if (len == 0)
    throw TError("len == 0", __func__, __FILE__, __LINE__);
  TVector<T> res(*this);

  if (left < right)
  {
    T pivot = res[(left + right) / 2];
    int i = left;
    int j = right;
    while (i <= j)
    {
      while (res[i] < pivot) i++;
      while (res[j] > pivot) j--;

      if (i <= j)
      {
        T reserv = res[i];
        res[i] = res[j];
        res[j] = reserv;
        i++;
        j--;
      }
    }
    if (left < j) 
      res = res.QuickSort(left, j);
    if (i < right)
      res = res.QuickSort(i, right);
  }

  return res;
}

template<class T>
inline TVector<T> TVector<T>::InsertionSort()
{
  if (len == 0)
    throw TError("len == 0", __func__, __FILE__, __LINE__);
  T key;
  TVector <T> res(*this);
  for (int i = 2; i < len; i)
  {
    key = res[i];
    int j = i - 1;
    while (j > 0 && res[j] > key)
    {
      res[j + 1] = res[j];
      j--;
    }
    res[j + 1] = key;
  }
  return res;
}

template<class T>
inline TVector<T> TVector<T>::Normalisation()
{
  if (len == 0)
    throw TError("len == 0", __func__, __FILE__, __LINE__);
  TVector<T> res(*this);
  return TVector <T> (res / res.InfinityNorm());
}

template<class T>
inline T TVector<T>::FirstNorm()
{
  if (len == 0)
    throw TError("len == 0", __func__, __FILE__, __LINE__);
  T first_norma = 0;
  for (int i = 0; i < len; ++i)
    first_norma += vector[i];
  return first_norma;
}

template<class T>
inline T TVector<T>::SecondNorm()
{
  if (len == 0)
    throw TError("len == 0", __func__, __FILE__, __LINE__);
  T second_norma = 0;
  for (int i = 0; i < len; ++i)
    second_norma += (vector[i] * vector[i]);
  return sqrt(second_norma);
}

template<class T>
inline T TVector<T>::InfinityNorm()
{
  if (len == 0)
    throw TError("len == 0", __func__, __FILE__, __LINE__);
  T maxi = vector[0];
  for (int i = 1; i < len; ++i)
  {
    if (vector[i] > maxi)
      maxi = vector[i];
  }
  return maxi;
}

template<class T>
inline T TVector<T>::HelderNorm()
{
  if (len == 0)
    throw TError("len == 0", __func__, __FILE__, __LINE__);
  T sum = 0;
  for (int i = 0; i < len; ++i)
    sum += pow(vector[i], (double)len);
  return pow(sum, 1 / (double)len);
}

template<class T>
inline void TVector<T>::Rand(int min,int max)
{
  static std::random_device rd;
  static std::mt19937 gen(rd());

  std::uniform_int_distribution<int> dist(min, max);
  for (int i =0;i<len;++i)
    vector[i] = dist(gen);
}


template<class T>
inline void TVector<T>::Save()
{
  FILE* file_of_numbers;
  file_of_numbers = fopen("result_massive.txt", "w");
  if (file_of_numbers != NULL)
  {
    fprintf(file_of_numbers, "Vector(%d):\n", len);
  }
  else
    printf("FILE ERROR!!!");
  for (int i = 0; i < len; ++i)
  {
      if (file_of_numbers != NULL)
      {
        fprintf(file_of_numbers, "%lf\t", vector[i]);
      }
      else
        printf("FILE ERROR!!!");
  }
  fclose(file_of_numbers);
}


template<class T>
inline TVectorIterator<T> TVector<T>::begin()
{
  return TVectorIterator<T>(*this, 0);
}

template<class T>
inline TVectorIterator<T> TVector<T>::end()
{
  return TVectorIterator<T>(*this, len);
}


template<class O>
inline ostream& operator<<(ostream& o, TVector<O>& t)
{
  if (t.vector == nullptr)
    o << "Len of vector: " << t.len << endl << "[]" << endl;
  else
  {
    o << "Len of vector: " << t.len << endl;
    for (int i = 0; i < t.len; ++i)
      o << t.vector[i] << " ";
  }
  o << endl;
  return o;
}

template<class I>
inline istream& operator>>(istream& i, TVector<I>& t)
{
  int len_;
  cout << "Enter the len of vector: ";
  i >> len_;
  if (len_<0)
    throw TError("len_ < 0", __func__, __FILE__, __LINE__);
  if (len_ == 0)
  {
    t.SetLen(len_);
    return i;
  }
  else
  {
    t.SetLen(len_);
    for (int k = 0; k < t.len; ++k)
    {
      cout << "vector[" << k << "] = ";
      i >> t.vector[k];
    }
    return i;
  }
}


template<class T>
inline TVectorIterator<T>::TVectorIterator(TVector<T>& vector, int index_) :
  p(vector), index(index_)
{
}

template<class T>
inline T& TVectorIterator<T>::operator*()
{
  return p[index];
}

template<class T>
inline TVectorIterator<T>& TVectorIterator<T>::operator++()
{
  index++;
  return *this;
}

template<class T>
inline TVectorIterator<T>& TVectorIterator<T>::operator++(int)
{
  index++;
  return*this;
}

template<class T>
inline bool TVectorIterator<T>::operator!=(const TVectorIterator<T>& p)
{
  return index != p.index;
}