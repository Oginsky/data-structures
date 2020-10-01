#pragma once
#include <fstream>

class Matrix {
	private:
		float **ptr;
		int size;
		float determinant;
		
		friend float lineONcoln(Matrix &l, Matrix &r, int ix, int jx);
		
	public:
		Matrix();
		Matrix (int );
		~Matrix();
		
		int det();
		int cofactor(int, int);
		void transposition();
		
		
		Matrix operator+(const Matrix&);
		Matrix operator-(const Matrix&);
		Matrix operator*(Matrix& right);
		friend Matrix operator*(float l, Matrix&);
		
		const Matrix& operator= (const Matrix&);
		Matrix& operator--();
		
		float& operator[](const int i);

		friend std::istream& operator>>(std::istream &, Matrix &);
		friend std::ostream& operator<<(std::ostream &, Matrix &);
};