#ifndef CML_MATRICES_H
#define CML_MATRICES_H

#include "./vectors.h"

#include <iostream>
#include <array>
#include <string>

namespace cml {


	// Matrix class definition

	template<typename T, int n, int m>
	class Matrix {

	private:

		std::array<T, n* m> comps{};

	public:

		int rows{ n };
		int cols{ m };

		Matrix() {};
		Matrix(std::initializer_list<std::initializer_list<T>> data);

		T get(int row, int col) const;
		void set(int row, int col, T value);
		void insert_row(int row, std::initializer_list<T> data);
		void insert_col(int col, std::initializer_list<T> data);

	};


	// Matrix class implementations

	template<typename T, int n, int m>
	Matrix<T, n, m>::Matrix(std::initializer_list <std::initializer_list<T>> data) {
		int i = 0, j = 0;
		for (const auto& l : data)
		{
			for (const auto& v : l)
			{
				comps[j + (i * m)] = v;
				++j;
			}
			j = 0;
			++i;
		}
	}

	template<typename T, int n, int m>
	T Matrix<T, n, m>::get (int row, int col) const {
		return comps[col + (row * m)];
	}

	template<typename T, int n, int m>
	void Matrix<T, n, m>::set(int row, int col, T value) {
		comps[col + (row * m)] = value;
	}

	template<typename T, int n, int m>
	void Matrix<T, n, m>::insert_row(int row, std::initializer_list<T> data) {
		if (row > (n - 1)) throw("Row access is trying to access out of bounds of matrix!");
		if (data.size() != m) throw("Row data size does not match the size of the matrix!");
		auto begin{ data.begin() };
		auto end{ data.end() };
		int i = 0;
		for (auto p{ begin }; p != end; ++p)
		{
			comps[i + (row * m)] = *p;
			i++;
		}
	}

	template<typename T, int n, int m>
	void Matrix<T, n, m>::insert_col(int col, std::initializer_list<T> data) {

	}


	// Operator overloading

	template<typename T, int n, int m>
	std::ostream& operator<< (std::ostream& out, const Matrix<T, n, m>& matrix) {

		// Determine column size
		std::array<int, m> column_sizes;
		for (int j = 0; j < m; j++) {

			int max_column_size{ 0 };

			for (int i = 0; i < n; i++) {

				T value{ matrix.get(i, j)};
				size_t column_size{ std::to_string(value).length() };

				if (column_size > max_column_size) {
					max_column_size = column_size;
				}
			}
			column_sizes[j] = max_column_size;
		}

		// Output matrix
		for (int i = 0; i < n; i++) {
			
			out << '|';
			
			for (int j = 0; j < m; j++) {
				
				T value{ matrix.get(i, j) };
				size_t value_size{ std::to_string(value).length() };
				if (value_size < column_sizes[j]) {
					for (int k = 0; k < (column_sizes[j] - (value_size - 1)); k++)
					{
						out << " ";
					}
					out << value;
				}
				else {
					out << " " << value;
				}
			}

			out << " |" << '\n';
		}
		return out;
	};

	template<typename T, int n, int m>
	Matrix<T, n, m> operator+ (const Matrix<T, n, m>& A, const Matrix<T, n, m>& B) {
		Matrix<T, n, m> result;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				result.set(i, j, A.get(i, j) + B.get(i, j));
			}
		}
		return result;
	}

	template<typename T, int n, int m>
	Matrix<T, n, m> operator- (const Matrix<T, n, m>& A, const Matrix<T, n, m>& B) {
		Matrix<T, n, m> result;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				result.set(i, j, A.get(i, j) - B.get(i, j));
			}
		}
		return result;
	}

	template<typename T, int n, int m>
	Matrix<T, n, m> operator* (T k, const Matrix<T, n, m>& A) {
		Matrix<T, n, m> result;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				result.set(i, j, k * A.get(i, j));
			}
		}
		return result;
	}

	template<typename T, int n, int m, int o, int p>
	Matrix<T, n, p> operator* (const Matrix<T, n, m>& A, const Matrix<T, o, p>& B) {
		Matrix<T, n, p> result;
		for (int i = 0; i < A.rows; i++)
		{
			for (int j = 0; j < B.cols; j++)
			{
				for (int k = 0; k < A.cols; k++)
				{
					result.set(i, j, result.get(i, j) + (A.get(i, k) * B.get(k, j)));
				}
			}
		}
		return result;
	}

	template<typename T, int n, int m, int o>
	Vector<T, o> operator* (const Matrix<T, n, m>& A, Vector<T, o>& vec) {
		Vector<T, o> result;
		for (int i = 0; i < A.rows; i++)
		{
			for (int j = 0; j < A.cols; j++)
			{
				result[i] = result[i] + A.get(i, j) * vec[j];
			}
		}
		return result;
	}


	// Creating special matrices functions

	template<typename T>
	Matrix<T, 4, 4> create_scaling_matrix(Vector<T, 3>& scale) {
		return Matrix<T, 4, 4>{
			{ scale[0], 0, 0, 0 },
			{ 0, scale[1], 0, 0 },
			{ 0, 0, scale[2], 0 },
			{ 0, 0,        0, 1 }
		};
	}

	template<typename T>
	Matrix<T, 4, 4> create_translation_matrix(Vector<T, 3>& translate) {
		return Matrix<T, 4, 4>{
			{ 1, 0, 0, translate[0] },
			{ 0, 1, 0, translate[1] },
			{ 0, 0, 1, translate[2] },
			{ 0, 0, 0,            1 }
		};
	}

	

}

#endif