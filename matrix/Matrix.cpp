#include <fstream>
#include <iostream>
#include <cmath>
#include "Matrix.h"
using namespace std;	

float lineONcoln(Matrix &l, Matrix& r, int ix, int jx) {
	float rez = 0;
	for (int i = 0; i < l.size; i++) rez += l.ptr[ix][i] * r.ptr[i][jx];
	return rez;
}


Matrix::Matrix() {
	size = determinant = -1;
	ptr = NULL;
}
Matrix::Matrix (int n){
	(n > 0) ? size = n : size = 0;
	size = n;
	ptr = new float*[size];
	for (int i = 0; i < size; i++) {
		ptr[i] = new float[size];
		for (int j = 0; j < size; j++)
			ptr[i][j] = 0;
	}
	determinant = -1;
}
Matrix::~Matrix(){
	for (int i = 0; i < size; i++)
		delete[] ptr[i], ptr[i] = NULL;
	delete[] ptr;
	ptr = NULL;
	size = 0;
	determinant = -1;
}

int Matrix::det(){
	if (determinant != -1) return determinant;
	if (size == 1) {
		determinant = ptr[0][0];
		return determinant;
	}
	if (size == 2) {
		determinant = ptr[0][0]*ptr[1][1] - ptr[0][1]*ptr[1][0];
		return determinant;
	}
	int rez = 0;
	for (int j = 0; j < size; j++) {
		if (!ptr[0][j]) continue;
		rez += ptr[0][j] * this->cofactor(0,j);
	}
	determinant = rez;
	return determinant;
}
int Matrix::cofactor(int ix, int jx){
	Matrix temp(size-1);
	int new_j = 0, new_i = 0;
	for (int i = 0; i < size; i++) {
		if (i == ix) continue;
		int new_j = 0;
		for (int j = 0; j < size; j++) {
			if (j == jx) continue;
			temp.ptr[new_i][new_j++] = ptr[i][j];
		}
		new_i++;
	}
	if ((ix+jx)%2) return (-1)*temp.det();
	else return temp.det();
}
void Matrix::transposition(){
	for (int i = 0; i < size; i++)
		for (int j = i; j < size; j++) {
			if (i == j) continue;
			int temp = ptr[i][j];
			ptr[i][j] = ptr[j][i];
			ptr[j][i] = temp;
		}
}

Matrix Matrix::operator+(const Matrix &right){
	if (size != right.size) cout << "Cложение матриц разного размера" , exit(1);
	Matrix rez(size);
	for (int i = 0; i < size-1; i++)
		for (int j = 0; j < size; j++)
			rez.ptr[i][j] = ptr[i][j] + right.ptr[i][j];
	return rez;
}
Matrix Matrix::operator-(const Matrix &right){
	if (size != right.size) cout << "Вычитание матриц разного размера" , exit(1);
	Matrix rez(size);
	for (int i = 0; i < size-1; i++)
		for (int j = 0; j < size; j++)
			rez.ptr[i][j] = ptr[i][j] - right.ptr[i][j];
	return rez;
}
Matrix Matrix::operator*(Matrix& right) {
//	if (size != right.size) cout << "Умножение матриц разного размера" , exit(1);
//	Matrix rez(size);
//	for (int i = 0; i < size; i++)
//		for (int j = 0; j < size; j++)
//			rez.ptr[i][j] = lineONcoln(*this, right, i, j);
//	return rez;

	double r;

    for (int i = 0; i < size; i++)
        for (int k = 0; k < size; k++) {
            r = ptr[i][k];
            for (int j = 0; j < size; j++)
                res.ptr[i][j] += r*right.ptr[k][j];
        }
}
Matrix operator*(float l, Matrix& m) {
	Matrix rez(m.size);
	for (int i = 0; i < m.size; i++) 
		for (int j = 0; j < m.size; j++)
			rez.ptr[i][j] = m.ptr[i][j] *= l;
	return rez;
}

const Matrix &Matrix::operator= (const Matrix &right){
	if (size != right.size) cout << "Присваивание матриц разного размера" , exit(1);
	size = right.size;
	determinant = right.determinant;
	for (int i = 0; i < right.size; i++)
		for (int j = 0; j < right.size; j++)
			ptr[i][j] = right.ptr[i][j];
	return *this;
}
Matrix& Matrix::operator--(){
	if (size == 1) cout << "Ошибка. Обратной матрицы размера 1х1 нет", exit(2);
	if (this->det() == 0) cout << "Обратной матрицы не существует так как определитель равен 0", exit(2);
	Matrix inverse(size); 
	inverse = *this;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			ptr[i][j] = inverse.cofactor(i,j);
	this->transposition();
	float mul = (float)1/inverse.det();
	*this = mul * *this;
	return *this;
}


float& Matrix::operator[](const int i) {
	return *ptr[i];
}


istream& operator>>(istream &is, Matrix &m) {
    for (int i = 0; i < m.size; i++)
    	for (int j = 0; j < m.size; j++)
    		is >> m.ptr[i][j];
    return is; 
}
ostream& operator<<(ostream &os, Matrix &m) {
	for (int i = 0; i < m.size; i++) {
		for (int j = 0; j < m.size; j++)
			cout << m.ptr[i][j] << " ";
		cout << endl;
	}
	return os;
}