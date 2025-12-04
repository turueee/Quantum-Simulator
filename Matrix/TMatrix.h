#pragma once

#include <iostream>
#include "TError.h"
#include "TComplex.h"

using namespace std;

template<class T>
class TMatrix {
protected:
    int rows;
    int columns;
    vector<vector<T>> matrix;
public:
    TMatrix();
    TMatrix(int n_, int m_);
    TMatrix(const TMatrix& table);
    TMatrix(TMatrix&& table) noexcept;
    ~TMatrix() = default;

    int GetRows() const;
    int GetColumns() const;
    void GetMatrix(vector<vector<T>>& array);

    void SetRows(int n_);
    void SetColumns(int m_);
    void SetMatrix(const vector<vector<T>>& array);

    TMatrix TenzorMul(const TMatrix<T>& other);
    TMatrix& operator=(const TMatrix<T>& table);
    TMatrix& operator=(TMatrix<T>&& table) noexcept;
    bool operator==(const TMatrix<T>& table);
    vector<T>& operator[](int index);
    const vector<T>& operator[](int index) const;

    template <class U>
    friend ostream& operator<<(ostream& o, TMatrix<U>& t);
    template <class U>
    friend istream& operator>>(istream& i, TMatrix<U>& t);
};

template<class T>
inline TMatrix<T>::TMatrix() : rows(0), columns(0)
{
}

template<class T>
inline TMatrix<T>::TMatrix(int n_, int m_)
{
    if (n_ < 0)
        throw TError("n_ < 0", __func__, __FILE__, __LINE__);
    else if (m_ < 0)
        throw TError("m_ < 0", __func__, __FILE__, __LINE__);
    else
    {
        rows = n_;
        columns = m_;
        matrix.resize(rows, vector<T>(columns, T(0)));
    }
}

template<class T>
inline TMatrix<T>::TMatrix(const TMatrix& table)
{
    rows = table.rows;
    columns = table.columns;
    matrix = table.matrix;
}

template<class T>
inline TMatrix<T>::TMatrix(TMatrix&& table) noexcept
{
    rows = table.rows;
    columns = table.columns;
    matrix = move(table.matrix);
    table.rows = 0;
    table.columns = 0;
}

template<class T>
inline int TMatrix<T>::GetRows() const
{
    return rows;
}

template<class T>
inline int TMatrix<T>::GetColumns() const
{
    return columns;
}

template<class T>
inline void TMatrix<T>::GetMatrix(vector<vector<T>>& array)
{
    array = matrix;
}

template<class T>
inline void TMatrix<T>::SetRows(int n_)
{
    if (n_ < 0)
        throw TError("n_ < 0", __func__, __FILE__, __LINE__);

    if (n_ == rows) return;

    matrix.resize(n_, vector<T>(columns, T(0)));
    rows = n_;
}

template<class T>
inline void TMatrix<T>::SetColumns(int m_)
{
    if (m_ < 0)
        throw TError("m_ < 0", __func__, __FILE__, __LINE__);

    if (m_ == columns) return;

    for (auto& row : matrix) {
        row.resize(m_, T(0));
    }
    columns = m_;
}

template<class T>
inline void TMatrix<T>::SetMatrix(const vector<vector<T>>& array)
{
    if (array.size() != rows || (rows > 0 && array[0].size() != columns))
        throw TError("size error", __func__, __FILE__, __LINE__);

    matrix = array;
}

template<class T>
TMatrix<T> TMatrix<T>::TenzorMul(const TMatrix<T>& other)
{
    int rows1 = GetRows();
    int cols1 = GetColumns();
    int rows2 = other.GetRows();
    int cols2 = other.GetColumns();

    TMatrix<T> res(rows1 * rows2, cols1 * cols2);

    for (int i1 = 0; i1 < rows1; ++i1) {
        for (int j1 = 0; j1 < cols1; ++j1) {
            for (int i2 = 0; i2 < rows2; ++i2) {
                for (int j2 = 0; j2 < cols2; ++j2) {
                    int res_i = i1 * rows2 + i2;
                    int res_j = j1 * cols2 + j2;
                    res[res_i][res_j] = (*this)[i1][j1] * other[i2][j2];
                }
            }
        }
    }
    return res;
}

template<class T>
inline TMatrix<T>& TMatrix<T>::operator=(const TMatrix<T>& table)
{
    if (this == &table)
        return *this;

    rows = table.rows;
    columns = table.columns;
    matrix = table.matrix;
    return *this;
}

template<class T>
inline TMatrix<T>& TMatrix<T>::operator=(TMatrix<T>&& table) noexcept
{
    if (this == &table)
        return *this;

    rows = table.rows;
    columns = table.columns;
    matrix = move(table.matrix);
    table.rows = 0;
    table.columns = 0;
    return *this;
}

template<class T>
inline bool TMatrix<T>::operator==(const TMatrix& table)
{
    if (rows != table.rows || columns != table.columns)
        return false;

    return matrix == table.matrix;
}

template<class T>
inline vector<T>& TMatrix<T>::operator[](int index)
{
    if (index < 0 || index >= rows)
        throw TError("index out of range", __func__, __FILE__, __LINE__);
    return matrix[index];
}

template<class T>
inline const vector<T>& TMatrix<T>::operator[](int index) const
{
    if (index < 0 || index >= rows)
        throw TError("index out of range", __func__, __FILE__, __LINE__);
    return matrix[index];
}

template<typename U>
inline ostream& operator<<(ostream& o, TMatrix<U>& t)
{
    if (t.rows == 0 || t.columns == 0)
    {
        o << "Size: 0 * 0.\n[]";
    }
    else
    {
        o << "Size: " << t.rows << " * " << t.columns << ".\n";
        for (int i = 0; i < t.rows; ++i)
        {
            o << "\t";
            for (int j = 0; j < t.columns; ++j)
            {
                o << t.matrix[i][j] << "\t";
            }
            o << endl;
        }
    }
    return o;
}

template <typename U>
inline istream& operator>>(istream& i, TMatrix<U>& t)
{
    cout << "Enter the count of strings: ";
    cin >> t.rows;
    cout << "Enter the count of columns: ";
    cin >> t.columns;

    if (t.rows < 0 || t.columns < 0)
        throw TError("invalid size", __func__, __FILE__, __LINE__);

    t.matrix.resize(t.rows, vector<I>(t.columns));

    for (int i = 0; i < t.rows; ++i)
    {
        for (int j = 0; j < t.columns; ++j)
        {
            cout << "matrix[" << i << "][" << j << "] = ";
            cin >> t.matrix[i][j];
        }
    }
    return i;
}