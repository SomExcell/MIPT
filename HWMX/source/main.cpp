#include "matrix.hpp"

#include <iostream>
#include <vector>

using namespace std;

int main()
{
	Matrix<int> matrix =Matrix<int>::eye(3,3);
	matrix[0][1] = 4;
	matrix[0][2] = 6;
	matrix[1][0] = 7;
	matrix[1][2] = 2;
	cout << matrix;
	cout << matrix.transpose();
	cout << matrix.transpose();
	return 0;
}
