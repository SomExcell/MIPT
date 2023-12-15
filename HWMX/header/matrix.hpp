#pragma once
#include <iostream>

template <typename T>class Matrix
{
public:

	Matrix(size_t cols, size_t rows, T val = T{});

	template<typename It>
	Matrix(size_t cols, size_t rows, It start, It fin) :cols(cols), rows(rows), size(cols* rows), data(new T[size])
	{
		if(typeid(T)!=typeid(It))

		for (size_t i = 0; i < cols; ++i)
		{
			for (size_t j = 0; j < rows; ++j)
			{
				data[i * rows + j] = static_cast<T>(*start);
				if (start == fin)
					break;
				++start;
			}
		}
	}

	static Matrix eye(size_t cols, size_t rows);

public:
	Matrix(const Matrix& rhs);
	Matrix(Matrix&& rhs);

	Matrix& operator=(const Matrix& rhs);
	Matrix& operator=(Matrix&& rhs);

	~Matrix();

public:
	size_t ncols() const;
	size_t nrows() const;

	T trace() const;
	bool equal(const Matrix& other) const;
	bool less(const Matrix& other) const;
	//void dump(std::ostream& os) const;
	int determinant();
	int det(int* metrix, unsigned int n);
	int* submatrix(int* matrix, unsigned int n, unsigned int x, unsigned int y);

public:

	Matrix& negate()&;
	Matrix& transpose()&;

public:
	struct ProxyRow
	{
		ProxyRow(T* row) :row(row) {};
		T* row;
		const T& operator[](size_t index)const { return row[index]; }
		T& operator[](size_t index) { return row[index]; }
	};
	ProxyRow operator[](size_t index)const
	{
		return  data + index * rows ;
	}
	
private:
	size_t cols = 0, rows = 0,size = 0;
	T* data = nullptr;
};

template <typename T> 
Matrix<T>::Matrix(size_t cols, size_t rows, T val = T{}) :cols(cols), rows(rows),size(cols*rows), data(new T[size])
{
	std::fill(data, data + size, val);
}

template<typename T>
Matrix<T> Matrix<T>::eye(size_t cols, size_t rows)
{
	Matrix<int> matrix(cols, rows);
	for (size_t i = 0; i < cols; ++i) { matrix[i][i] = 1; }
	return matrix;
}

template<typename T>
Matrix<T>::Matrix(const Matrix& rhs):cols(rhs.ncols()),rows(rhs.nrows()),size(rhs.cols*rhs.rows)
{
	delete[] data;
	data = new T[size];
	for (size_t i = 0; i < cols; ++i)
	{
		for (size_t j = 0; j < rows; ++j)
		{
			data[i*rows+j] = rhs.data[i*rows+j];
		}
	}
}

template<typename T>
Matrix<T>::Matrix(Matrix&& rhs):cols(rhs.ncols()), rows(rhs.nrows()), size(rhs.cols* rhs.rows) 
{
	delete[] data;
	data = rhs.data;
	rhs.data = nullptr;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& rhs)
{
	if (this == &rhs)
		return *this;
	cols = rhs.cols(), rows = rhs.rows(), size = rhs.cols() * rhs.rows();
	delete[] data;
	data = new T[size];
	for (size_t i = 0; i < cols; ++i)
	{
		for (size_t j = 0; j < rows; ++j)
		{
			data[i * rows + j] = rhs.data[i * rows + j];
		}
	}
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& rhs)
{
	if(this == &rhs)
		*return 
	cols = rhs.cols(), rows = rhs.rows(), size = rhs.cols() * rhs.rows();
	delete[] data;
	data = rhs.data;
	rhs.data = nullptr;
	return *this;
}

template<typename T>
Matrix<T>::~Matrix()
{
	delete[] data;
}

template<typename T>
size_t Matrix<T>::ncols()const
{
	return cols;
}

template<typename T>
size_t Matrix<T>::nrows()const
{
	return rows;
}

template<typename T>
T Matrix<T>::trace()const
{
	size_t place = 0;
	T result = T{};
	for (size_t i = 0; i < cols; ++i)
	{
		result += data[place];
		place += rows + 1;
	}
	return result;
}

template<typename T>
bool Matrix<T>::equal(const Matrix& other)const
{
	if (this == &other)
		return true;
	if (cols != other.cols || rows != other.rows)
		return false;
	for (size_t i = 0; i < cols; ++i)
	{
		for (size_t j = 0; j < rows; ++j)
		{
			if (data[i * rows + j] != other.data[i * rows + j])
				return false;
		}
	}
	return true;
}

template<typename T>
bool Matrix<T>::less(const Matrix& other)const
{
	if (this == &other)
		return false;
	if (cols < other.cols || rows < other.rows)
		return true;
	for (size_t i = 0; i < cols; ++i)
	{
		for (size_t j = 0; j < rows; ++j)
		{
			if (data[i*rows+j] < other.data[i*rows+j])
				return true;
		}
	}
	return false;
}

template<typename T>
int* Matrix<T>::submatrix( int *matrix,unsigned int n, unsigned int x, unsigned int y)
{
	int* submatrix = new int [(n -1)*(n-1)];
	int subi = 0;
	for (int i = 0; i < n; i++) {
		int subj = 0;
		if (i == y) {
			continue;
		}
		for (int j = 0; j < n; j++) {
			if (j == x) {
				continue;
			}
			submatrix[subi*(n-1)+subj] = matrix[i * n + j];
			subj++;
		}
		subi++;
	}
	return submatrix;
}

template<typename T>
int Matrix<T>::det(int* matrix, unsigned int n)
{
	int d = 0;
	if (n == 2) {
		return matrix[0] * matrix[1*n+1] - matrix[1*n+0] * matrix[1];
	}
	for (int x = 0; x < n; ++x) {
		d += ((x % 2 == 0 ? 1 : -1) * matrix[x] * det(submatrix(matrix, n, x, 0), n - 1));
	}

	return d;
}

template<typename T>
int Matrix<T>::determinant()
{
	return det(data, cols);
}

template<typename T>
Matrix<T>& Matrix<T>::negate()&
{
	for (size_t i = 0; i < cols; ++i)
	{
		for (size_t j = 0; j < rows; ++j)
		{
			data[i * rows + j] = -data[i * rows + j];
		}
	}
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::transpose()&
{
	
	for (size_t i = 0; i < cols; ++i)
	{
		for (size_t j = i; j < rows; ++j)
		{
			std::swap(data[i * rows + j], data[j * cols +i]);
		}
	}
	return *this;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, Matrix<T>& matrix)
{
	size_t cols = matrix.ncols(), rows = matrix.nrows(),i,j;
	for (i = 0; i < cols; ++i)
	{
		for ( j = 0; j < rows; ++j)
		{
			out << matrix[i][j]<< " ";
		}
		out << std::endl;
	}
	return out;
}