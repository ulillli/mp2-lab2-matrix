// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>

class TDynamicVector
{
   //const T ZERO = 0;
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if ((sz<0)||(sz>MAX_VECTOR_SIZE))
    throw out_of_range("Vector size should be greater than zero and smaller than max_vector_size");
    pMem = new T[sz](); // {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector & v)
  {
      this->sz = v.size();
      this->pMem = new T[sz];
      std::copy(v.pMem, v.pMem + this->sz, this->pMem);
  }
  TDynamicVector(TDynamicVector && v) noexcept
  {
      this->pMem = v.pMem;
      this->sz = v.size();
      v.pMem = nullptr;
      v.sz = 0;
  }
  ~TDynamicVector()
  {
      if (this->pMem != nullptr) delete[] this->pMem;
  }
  TDynamicVector & operator=(const TDynamicVector& v)
  {
      if (v != *this) {
          if (this->pMem != nullptr) { //проверяем не нулевой ли указатель 
              delete[] this->pMem;
          }
          this->sz = v.size();
          this->pMem = new T[this->sz];
          std::copy(v.pMem, v.pMem + v.size(), this->pMem);
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      this->pMem = v.pMem;
      this->sz = v.size();
      v.pMem = nullptr;
      v.sz = 0;
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  { 
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if ((ind>=0) && (ind < this->sz)) {
          return pMem[ind];
      }
      else throw "Index out of range\n";
  }
  const T& at(size_t ind) const
  {
      if ((ind >=0) && (ind < this->sz)) {
          return pMem[ind];
      }
      else throw "Index out of range\n";
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      bool flag = 1;
      if (this->sz != v.sz) flag = 0;
      else {
          for (int i = 0; i < this->sz; i++) {
              if (this->pMem[i] != v.pMem[i]) {
                  flag = 0;
                  break;
              }
          }
      }
      return flag;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this== v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector tmp(*this);
      for (int i = 0; i < tmp.sz; i++) {
          tmp.pMem[i] = tmp.pMem[i]+val;
      }
      return tmp;
  }
  TDynamicVector operator-(double val)
  {
      TDynamicVector tmp(*this);
      for (int i = 0; i < tmp.sz; i++) {
          tmp.pMem[i] = tmp.pMem[i]-val;
      }
      return tmp;
  }
  TDynamicVector operator*(double val)
  {
      TDynamicVector tmp(*this);
      for (int i = 0; i < tmp.sz; i++) {
          tmp.pMem[i] = tmp.pMem[i]*val;
      }
      return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (this->sz == v.sz) {
          TDynamicVector tmp(*this);
          for (int i = 0; i < tmp.sz; i++) {
              tmp.pMem[i] = tmp.pMem[i]+v.pMem[i];
          }
          return tmp;
      }
      else throw "Can't add vector of not equal size";
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (this->sz == v.sz) {
          TDynamicVector tmp(*this);
          for (int i = 0; i < tmp.sz; i++) {
              tmp.pMem[i]=tmp.pMem[i] - v.pMem[i];
          }
          return tmp;
      }
      else throw "Can't subtract vector of not equal size";
  }
  T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))
  {
      if (this->sz == v.sz) {
          T result=0;
          for (int i = 0; i < v.sz; i++) {
              result += this->pMem[i] * v.pMem[i];
          }
          return result;
      }
      else throw "Can't * vector of not equal size";
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if ((s <= MAX_MATRIX_SIZE) && (s > 0)) {
          for (size_t i = 0; i < sz; i++)
              pMem[i] = TDynamicVector<T>(sz);
      }
      else throw "Can't creat a matrix with a not right size";
  }
  TDynamicMatrix(const TDynamicVector<TDynamicVector<T>>& v) : TDynamicVector<TDynamicVector<T>>(v)
  {
      if ((sz > MAX_MATRIX_SIZE) || (sz <= 0)) {
          throw "Can't creat a matrix with a not right size";
      }
  }
  operator TDynamicVector<TDynamicVector<T>>() {
      TDynamicVector<TDynamicVector<T>> result(sz);
          for (int i = 0; i < sz; i++) {
              result[i] = pMem[i];
          }
      return result;
  }
  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;
  T & at(size_t i, size_t j)
  {
      if ((i>= 0) && (i< this->sz) && (j >= 0) && (j < this->sz)) {
          return pMem[i][j];
      }
      else throw "Index out of range\n";
  }
  const T& at(size_t i, size_t j) const
  {
      if ((i >= 0) && (i < this->sz) && (j >=0) && (j < this->sz)) {
          return pMem[i][j];
      }
      else throw "Index out of range\n";
  }
  // сравнение
  bool operator==(const TDynamicMatrix & m) const noexcept
  {
      bool flag = 1; 
      if (this->sz == m.size()) {
          for (int i = 0; i < this->sz; i++) {
              if (this->pMem[i] != m[i]) {
                  flag = 0;
                  break;
              }
          }
      }
      else flag = 0;
      return flag;
  }

  // матрично-скалярные операции
  TDynamicMatrix<T> operator*(const T & val)
  {
      TDynamicVector<TDynamicVector<T>> result = TDynamicVector<TDynamicVector<T>>(*this)*val;
      return result;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T> & v)
  {
      TDynamicVector<T> result=TDynamicVector<TDynamicVector<T>>(*this)*v;
      return result; 
  }
  TDynamicMatrix transposition() const{
      TDynamicMatrix result(*this);
          for (int i = 0; i < this->sz; i++) {
              for (int j = 0; j < this->sz; j++) {
                  result[i][j] = this->at(j,i);
              }
          }
          //std::cout << result;
   
          return result;
  }
  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      TDynamicVector<TDynamicVector<T>> result = TDynamicVector<TDynamicVector<T>>(*this) + TDynamicVector<TDynamicVector<T>>(m);
      return result;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      TDynamicVector<TDynamicVector<T>> result = TDynamicVector<TDynamicVector<T>>(*this) - TDynamicVector<TDynamicVector<T>>(m);
      return result;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      TDynamicMatrix tmp(m.transposition()), result(this->sz);
      for (int i = 0; i < this->sz; i++) {
          for (int j = 0; j < this->sz; j++) {
              result[i][j] = pMem[i] * tmp[i];
          }
      }
      return result;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.size(); i++)
          istr >> v[i]; // требуется оператор>> для типа T
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.size(); i++)
          ostr << v[i] << std::endl; // требуется оператор << для типа T
      return ostr;
  }
};

#endif
