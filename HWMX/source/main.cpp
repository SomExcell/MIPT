#include <matrix.hpp>

#include <iostream>
#include <vector>

using namespace std;

int main()
{
	Matrix<int> matrix1 = Matrix<int>::eye(4,4);
	cout << matrix1;
	matrix1[0][1] = 2;
	matrix1[1][0] = 2;
	matrix1[2][3] = 3;
	matrix1[3][2] = 3;
	cout << matrix1.determinant()<<endl;
	cout << matrix1;
	return 0;
}
