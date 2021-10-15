#pragma once
#include <cassert>
#include <vector>
#include <iostream>

template<class T>
class Matrix
{
public:
	Matrix(size_t rowsCount, size_t colsCount)
		:rowsCount_(rowsCount),
		colsCount_(colsCount),
		data_(rowsCount, std::vector<T>(colsCount)) {}

	Matrix(std::vector<std::vector<T>> data)
		:rowsCount_(data.size()),
		colsCount_(data.size() > 0 ? data[0].size() : 0),
		data_(std::move(data)) {}

	Matrix() :Matrix(0, 0) {}

	Matrix(const Matrix& other)
		: rowsCount_(other.rowsCount_),
		colsCount_(other.colsCount_),
		data_(other.data_) {}

	Matrix(Matrix&& other) noexcept
		: rowsCount_(other.rowsCount_),
		colsCount_(other.colsCount_),
		data_(std::move(other.data_)) {}

	size_t RowsCount() const
	{
		return rowsCount_;
	}

	size_t ColsCount() const
	{
		return colsCount_;
	}

	void swap(Matrix& other)
	{
		std::swap(colsCount_, other.colsCount_);
		std::swap(rowsCount_, other.rowsCount_);
		std::swap(data_, other.data_);
	}

	Matrix& operator=(Matrix other)
	{
		swap(other);
		return *this;
	}

	//Indexing
	std::vector<T>& operator[](size_t i);

	const std::vector<T>& operator[](size_t i) const;

	using DataT = std::vector<std::vector<T>>;
	// Iterators methods
	typename DataT::iterator begin() noexcept;

	typename DataT::const_iterator begin() const noexcept;

	typename DataT::iterator end() noexcept;

	typename DataT::const_iterator end() const noexcept;

	// math operations
	Matrix operator*(const Matrix& other) const;

	void InsertBack(const Matrix<T>& other);

private:
	size_t rowsCount_, colsCount_;
	std::vector<std::vector<T>> data_;
};

template <class T>
std::vector<T>& Matrix<T>::operator[](size_t i)
{
	return data_[i];
}

template <class T>
const std::vector<T>& Matrix<T>::operator[](size_t i) const
{
	return data_[i];
}

template <class T>
typename std::vector<std::vector<T>>::iterator Matrix<T>::begin() noexcept
{
	return data_.begin();
}

template <class T>
typename std::vector<std::vector<T>>::const_iterator Matrix<T>::begin() const noexcept
{
	return data_.begin();
}

template <class T>
typename std::vector<std::vector<T>>::iterator Matrix<T>::end() noexcept
{
	return data_.end();
}

template <class T>
typename std::vector<std::vector<T>>::const_iterator Matrix<T>::end() const noexcept
{
	return data_.end();
}

template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix& other) const
{
	assert(colsCount_ == other.rowsCount_);

	Matrix res(rowsCount_, other.colsCount_);
	for (size_t i = 0; i < rowsCount_; i++) {
		for (size_t j = 0; j < other.colsCount_; j++)
		{
			T sum = 0;
			for (size_t k = 0; k < colsCount_; k++)
				sum += (*this)[i][k] * other[k][j];
			res[i][j] = sum;
		}
	}
	return res;
}

template <class T>
void Matrix<T>::InsertBack(const Matrix<T>& other)
{
	data_.insert(data_.end(), other.data_.begin(), other.data_.end());
	rowsCount_ = data_.size();
	colsCount_ = data_.size() > 0 ? data_[0].size() : 0;
}


template<class T>
std::vector<T> operator+(const std::vector<T>& a, const std::vector<T>& b) {
	std::vector<T> res = a;
	for (int i = 0; i < a.size(); i++)
		res[i] += b[i];
	return res;
}

// Input matrix from stream
template <class T>
std::istream& operator>>(std::istream& in, Matrix<T>& matrix)
{
	for (auto&& row : matrix)
		for (auto&& elem : row)
			in >> elem;
	return in;
}

