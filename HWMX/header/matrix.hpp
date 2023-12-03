#pragma once
#include <iostream>

template <typename T>class Matrix
{
public:

	Matrix(size_t cols, size_t rows, T val = T{});

	//template<typename It>
	//Matrix(int cols, int rows, It start, It fin);

	static Matrix eye(size_t cols, size_t rows);

public:
	Matrix(const Matrix& rhs);
	Matrix(Matrix&& rhs);

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
			data[i*rows+j] = rhs[i][j];
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
			out << matrix[i][j]<< " ";
		}
		out << std::endl;
	}
	return out;
}