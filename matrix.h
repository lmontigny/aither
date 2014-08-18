#ifndef MATRIXHEADERDEF             //only if the macro MATRIXHEADERDEF is not defined execute these lines of code
#define MATRIXHEADERDEF             //define the macro

#include <vector>  //vector
#include <string>  //string
#include <math.h>       //sqrt
#include <iostream>
#include "primVars.h"
#include "eos.h"

using std::vector;
using std::string;
using std::ostream;

//class to store a column matrix
class colMatrix {
  int size;
  double *data;

 public:
  //constructor
  colMatrix( const int &a ): size(a) {data = new double[a];}
  colMatrix() : size(0), data(NULL){}

  //copy constructor
  colMatrix( const colMatrix &cp);

  //copy assignment operator
  colMatrix& operator= (colMatrix other);

  //move constructor
  colMatrix(colMatrix &&other) : colMatrix() {
    swap(*this,other);
    other.data=NULL;
  }

  //member functions
  double Data(const int &)const;
  void SetData(const int &, const double&);
  int Size()const{return size;}
  void Zero();
  double Sum();

  //operator overloads
  colMatrix operator + (const colMatrix&)const;
  colMatrix operator - (const colMatrix&)const;
  colMatrix operator * (const colMatrix&)const;
  colMatrix operator / (const colMatrix&)const;

  colMatrix operator + (const vector<double>&)const;
  colMatrix operator - (const vector<double>&)const;

  colMatrix operator + (const double&)const;
  colMatrix operator - (const double&)const;
  colMatrix operator * (const double&)const;
  colMatrix operator / (const double&)const;

  friend colMatrix operator + (const double&, const colMatrix&);
  friend colMatrix operator - (const double&, const colMatrix&);
  friend colMatrix operator * (const double&, const colMatrix&);
  friend colMatrix operator / (const double&, const colMatrix&);
  friend ostream & operator<< (ostream &os, const colMatrix&);

  friend void swap(colMatrix &first, colMatrix &second);

  //destructor
  ~colMatrix() {
    delete [] data;
    data = NULL;
  }

};


//class to store a square matrix
class squareMatrix {
  int size;
  double *data;

 public:
  //constructor
  squareMatrix( const int &a ): size(a) {data = new double[a*a];}
  squareMatrix() : size(0), data(NULL){}

  //copy constructor
  squareMatrix( const squareMatrix &cp);

  //copy assignment operator
  squareMatrix& operator= (squareMatrix other);
  //squareMatrix& operator= (const squareMatrix &other);

  //move constructor
  squareMatrix(squareMatrix &&other) : squareMatrix() {
    swap(*this,other);
    other.data=NULL;
  }

  //member functions
  double Data(const int &, const int &)const;
  void SetData(const int &, const int &, const double&);
  int Size()const{return size;}
  void SwapRows(const int &, const int &);
  void Inverse();
  int FindMaxInCol(const int &, const int &, const int &)const;
  void RowMultiply(const int &, const int &, const double &);
  void LinCombRow(const int &, const double &, const int &);
  void Zero();
  void Identity();
  colMatrix Multiply( const colMatrix & )const;

  //operator overloads
  squareMatrix operator + (const squareMatrix&)const;
  squareMatrix operator - (const squareMatrix&)const;
  squareMatrix operator * (const squareMatrix&)const;

  squareMatrix operator + (const double&)const;
  squareMatrix operator - (const double&)const;
  squareMatrix operator * (const double&)const;
  squareMatrix operator / (const double&)const;

  friend squareMatrix operator + (const double&, const squareMatrix&);
  friend squareMatrix operator - (const double&, const squareMatrix&);
  friend squareMatrix operator * (const double&, const squareMatrix&);
  friend squareMatrix operator / (const double&, const squareMatrix&);
  friend ostream & operator<< (ostream &os, const squareMatrix&);

  friend void swap(squareMatrix &first, squareMatrix &second);

  //destructor
  ~squareMatrix() {
    delete [] data;
    data = NULL;
  }

};

//Class to store the implicit flux jacobians for the entire mesh. Only values on populated diagonals are stored.
class matrixDiagonal {
  int size;
  squareMatrix *data;

 public:
  //constructor
  matrixDiagonal( const int &a ): size(a) {data = new squareMatrix[a];}
  matrixDiagonal() : size(0), data(NULL){}

  //copy constructor
  matrixDiagonal( const matrixDiagonal &cp);

  //copy assignment operator
  matrixDiagonal& operator= (matrixDiagonal other);

  //move constructor
  matrixDiagonal(matrixDiagonal &&other) : matrixDiagonal() {
    swap(*this,other);
    other.data=NULL;
  }

  //member functions
  squareMatrix Data(const int &)const;
  void SetData(const int &, const squareMatrix&);
  int Size()const{return size;}
  void Zero(const int &);
  void CleanResizeZero(const int &, const int &);
  void Inverse();

  //operator overloads
  friend ostream & operator<< (ostream &os, const matrixDiagonal&);

  friend void swap(matrixDiagonal &first, matrixDiagonal &second);

  //destructor
  ~matrixDiagonal() {
    delete [] data;
    data = NULL;
  }

};


//function declarations
double SymGaussSeidel( matrixDiagonal &, const matrixDiagonal &, const matrixDiagonal &, const matrixDiagonal &, const matrixDiagonal &, const matrixDiagonal &, const matrixDiagonal &,
		       vector<colMatrix> &, const vector<colMatrix> &, const vector<primVars> &, const vector<primVars> &, const int &, const double &, const int &, const int &, const idealGas &);

#endif
