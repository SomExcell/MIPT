#pragma once
#include <iostream>

template <typename T>class Matrix
{
public:

	Matrix() {};

	Matrix(size_t cols, size_t rows, T val = T{});

	//template<typename It>
	//Matrix(int cols, int rows, It start, It fin);

	//static Matrix eye(int n, int m);

public:
	//Matrix(const Matrix& rhs);
	//Matrix(Matrix&& rhs) noexcept;

	//Matrix& operator=(const Matrix& rhs);
	//Matrix& operator=(Matrix&& rhs) noexcept;

	//~Matrix();

public:
	size_t ncols() const;
	size_t nrows() const;

	//T trace() const;
	//bool equal(const Matrix& other) const;
	//bool less(const Matrix& other) const;
	//void dump(std::ostream& os) const;

public:

	//Matrix& negate()&;

	//Matrix& transpose()&;

	//bool equal(const Matrix& other) const;

public:
	
	

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
size_t Matrix<T>::ncols()const
{
	return cols;
}

template<typename T>
size_t Matrix<T>::nrows()const
{
	return rows;
}



template <typename T>
std::ostream& operator<<(std::ostream& out, Matrix<T>& matrix)
{
	size_t cols = matrix.ncols(), rows = matrix.nrows(),i,j;
	for (i = 0; i < cols; ++i)
	{
		for ( j = 0; j < rows; ++j)
		{
			
		}
	}
}