#pragma once
#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

using namespace std;
template <class T>
class TComplex
{
protected:
  T re;
  T im;
public:
  TComplex();
  TComplex(T re_, T im_);
  TComplex(const TComplex& p);

  T GetRe();
  T GetIm();

  void SetRe(T re_);
  void SetIm(T im_);


  TComplex operator+ (const TComplex<T>& p);
  TComplex operator- (const TComplex<T>& p);
  TComplex operator* (const TComplex<T>& p);
  TComplex operator/ (const TComplex<T>& p);

  TComplex operator+= (const TComplex<T>& p);
  TComplex operator-= (const TComplex<T>& p);
  TComplex operator*= (const TComplex<T>& p);
  TComplex operator/= (const TComplex<T>& p);

  TComplex operator=(const TComplex<T>& p);

  bool operator!=(const TComplex<T>& p);
  bool operator==(const TComplex<T>& p);

  T Abs();
  TComplex<T> Pow(double st);
  TComplex<T> ImPow(TComplex<T> st);
  void PrintTrig();

  template<class D>
  friend ostream& operator<<(ostream& o, TComplex<D>& b);

  template<class D>
  friend istream& operator>>(istream& i, TComplex<D>& b);
};


#include "TComplex.h"
template<class T>
inline TComplex<T>::TComplex()
{
  re = 0;
  im = 0;
}


template<class T>
inline TComplex<T>::TComplex(T re_, T im_)
{
  re = re_;
  im = im_;
}


template<class T>
inline TComplex<T>::TComplex(const TComplex& p)
{
  re = p.re;
  im = p.im;
}


template<class T>
inline T TComplex<T>::GetRe()
{
  return this->re;
}


template<class T>
inline T TComplex<T>::GetIm()
{
  return this->im;
}


template<class T>
inline void TComplex<T>::SetRe(T re_)
{
  this->re = re_;
}


template<class T>
inline void TComplex<T>::SetIm(T im_)
{
  this->im = im_;
}


template<class T>
inline TComplex<T> TComplex<T>::operator+(const TComplex<T>& p)
{
  return TComplex(re + p.re, im + p.im);
}


template<class T>
inline TComplex<T> TComplex<T>::operator-(const TComplex<T>& p)
{
  return TComplex(re - p.re, im - p.im);
}


template<class T>
inline TComplex<T> TComplex<T>::operator*(const TComplex<T>& p)
{
  return TComplex(re * p.re - im * p.im, re * p.im + im * p.re);
}


template<class T>
inline TComplex<T> TComplex<T>::operator/(const TComplex<T>& p)
{
  if (p.im == 0 && p.re == 0)
    throw("Division by zero");
  return TComplex((re * p.re + im * p.im) / (p.re * p.re + p.im * p.im), (im * p.re - re * p.im) / (p.re * p.re + p.im * p.im));
}


template<class T>
inline TComplex<T> TComplex<T>::operator+=(const TComplex<T>& p)
{
  re += p.re;
  im += p.im;
  return *this;
}


template<class T>
inline TComplex<T> TComplex<T>::operator-=(const TComplex<T>& p)
{
  re -= p.re;
  im -= p.im;
  return *this;
}


template<class T>
inline TComplex<T> TComplex<T>::operator*=(const TComplex<T>& p)
{
  T re_ = re;
  re = (re_ * p.re - im * p.im);
  im = (re_ * p.im + im * p.re);
  return *this;
}


template<class T>
inline TComplex<T> TComplex<T>::operator/=(const TComplex<T>& p)
{
  if (p.im == 0 && p.re == 0)
    throw("Division by zero");
  T re_ = re;
  re = (re_ * p.re + im * p.im) / (p.re * p.re + p.im * p.im);
  im = (im * p.re - re_ * p.im) / (p.re * p.re + p.im * p.im);
  return *this;
}


template<class T>
inline TComplex<T> TComplex<T>::operator=(const TComplex<T>& p)
{
  re = p.re;
  im = p.im;
  return *this;
}


template<class T>
inline bool TComplex<T>::operator!=(const TComplex<T>& p)
{
  if (re == p.re && im == p.im)
    return 0;
  else
    return 1;
}


template<class T>
inline bool TComplex<T>::operator==(const TComplex<T>& p)
{
  if (re == p.re && im == p.im)
    return 1;
  else
    return 0;
}


template<class T>
inline T TComplex<T>::Abs()
{
  return pow(re * re + im * im, 0.5);
}


template<class T>
inline TComplex<T> TComplex<T>::Pow(double st)
{
  if (re == 0 && im == 0 && st == 0)
    throw("Uncertainty");
  if (re > 0)
    return TComplex(pow(pow(re * re + im * im, 0.5), st) * cos(atan(im / re) * st), pow(pow(re * re + im * im, 0.5), st) * sin(atan(im / re) * st));
  else
  {
    if (re < 0 && im >= 0)
      return TComplex(pow(pow(re * re + im * im, 0.5), st) * cos((M_PI + atan(im / re)) * st), pow(pow(re * re + im * im, 0.5), st) * sin((M_PI + atan(im / re)) * st));
    else
    {
      if (re < 0 && im < 0)
        return TComplex(pow(pow(re * re + im * im, 0.5), st) * cos((-M_PI + atan(im / re)) * st), pow(pow(re * re + im * im, 0.5), st) * sin((-M_PI + atan(im / re)) * st));
      else
      {
        if (re == 0 && im > 0)
          return TComplex(pow(pow(re * re + im * im, 0.5), st) * cos((M_PI / 2) * st), pow(pow(re * re + im * im, 0.5), st) * sin((M_PI / 2) * st));
        else
        {
          return TComplex(pow(pow(re * re + im * im, 0.5), st) * cos((-M_PI / 2) * st), pow(pow(re * re + im * im, 0.5), st) * sin((-M_PI / 2) * st));
        }
      }
    }
  }
}


template<class T>
inline TComplex<T> TComplex<T>::ImPow(TComplex<T> st)
{
  if ((im == 0 && re == 0 && st.re == 0) || (im == 0 && re == 0 && st.re < 0 && st.im == 0))
  {
    throw "Uncertainty";
  }
  if (im == 0 && re == 0 && st.re > 0 && st.im == 0)
    return TComplex<double>(0,0);
  else
  {
    double fi;
    if (re > 0)
      fi = atan(im / re);
    else
    {
      if (re < 0 && im >= 0)
        fi = M_PI + atan(im / re);
      else
      {
        if (re < 0 && im < 0)
          fi = -M_PI + atan(im / re);
        else
        {
          if (re == 0 && im > 0)
            fi = M_PI / 2;
          else
          {
            fi = -M_PI / 2;
          }
        }
      }
    }
    TComplex<T> res(round(pow(M_E,st.re*log(pow(im * im + re * re, 0.5))-fi*st.im)*cos(fi*st.re+st.im*log(pow(im * im + re * re, 0.5)))*100000)/100000, round(pow(M_E, st.re * log(pow(im * im + re * re, 0.5)) - fi * st.im) * sin(fi * st.re + st.im * log(pow(im * im + re * re, 0.5)))*100000)/100000);
    return res;
  }
}


template<class T>
inline void TComplex<T>::PrintTrig()
{
  if (re > 0)
    cout << pow(re * re + im * im, 0.5) << " * (cos(" << atan(im / re) * 180 / M_PI << ") + isin(" << atan(im / re) * 180 / M_PI << "))" << endl;
  else
  {
    if (re < 0 && im >= 0)
      cout << pow(re * re + im * im, 0.5) << " * (cos(" << (M_PI + atan(im / re)) * 180 / M_PI << ") + isin(" << (M_PI + atan(im / re)) * 180 / M_PI << "))" << endl;
    else
    {
      if (re < 0 && im < 0)
        cout << pow(re * re + im * im, 0.5) << " * (cos(" << (-M_PI + atan(im / re)) * 180 / M_PI << ") + isin(" << (-M_PI + atan(im / re)) * 180 / M_PI << "))" << endl;
      else
      {
        if (re == 0 && im > 0)
          cout << pow(re * re + im * im, 0.5) << " * (cos(" << 90 << ") + isin(" << 90 << "))" << endl;
        else
        {
          cout << pow(re * re + im * im, 0.5) << " * (cos(" << -90 << ") + isin(" << -90 << "))" << endl;
        }
      }
    }
  }
}


template<typename D>
inline ostream& operator<<(ostream& o, TComplex<D>& b)
{
  if (b.im >= 0)
    o << b.re << " + " << b.im << "i" << endl;
  else
    o << b.re << " - " << -b.im << "i" << endl;
  return o;
}


template<typename D>
inline istream& operator>>(istream& i, TComplex<D>& b)
{
  D re_, im_;
  cout << "Enter a real part of number: " << endl;
  i >> re_;
  cout << "Enter an imaginary part of number: " << endl;
  i >> im_;
  b.SetRe(re_);
  b.SetIm(im_);
  return i;
}
