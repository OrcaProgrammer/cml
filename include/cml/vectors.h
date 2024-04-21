#ifndef CML_VECTORS_H
#define CML_VECTORS_H

#include <iostream>
#include <array>
#include <cmath>

namespace cml {


	// Forward declarations to allow operator overloading for templates	

	template<typename T, int size> class Vector;
	template<typename T, int size> std::ostream& operator<< (std::ostream& out, const Vector<T, size>& vec);
	template<typename T, int size> Vector<T, size> operator+ (const Vector<T, size>& a, const Vector<T, size>& b);
	template<typename T, int size> Vector<T, size> operator- (const Vector<T, size>& a, const Vector<T, size>& b);
	template<typename T, int size> Vector<T, size> operator* (T k, const Vector<T, size>& a);
	template<typename T, int size> T vector_length(const Vector<T, size>& a);
	template<typename T, int size> T dot_product(const Vector<T, size>& a, const Vector<T, size>& b);
	template<typename T> Vector<T, 3> cross_product(const Vector<T, 3>& a, const Vector<T, 3>& b);


	// Vector class definition

	template <typename T, int size>
	class Vector {
	
	private:

		std::array<T, size> comps{};

	public:

		Vector() {};
		Vector(std::array<T, size> vec);
		Vector(std::initializer_list<T> vec);

		T& operator[](int index);
		friend std::ostream& operator<< <> (std::ostream& out, const Vector<T, size>& vec);
		friend Vector<T, size> operator+ <> (const Vector<T, size>& a, const Vector<T, size>& b);
		friend Vector<T, size> operator- <> (const Vector<T, size>& a, const Vector<T, size>& b);
		friend Vector<T, size> operator* <> (T k, const Vector<T, size>& a);
		friend T vector_length <> (const Vector<T, size>& a);
		friend T dot_product <> (const Vector<T, size>& a, const Vector<T, size>& b);
		friend Vector<T, 3> cross_product <> (const Vector<T, 3>& a, const Vector<T, 3>& b);
	};


	// Vector class implementations

	template<typename T, int size>
	Vector<T, size>::Vector(std::array<T, size> vec) : comps(vec) {};

	template<typename T, int size>
	Vector<T, size>::Vector(std::initializer_list<T> vec) {
		if (vec.size() != size) throw("Vector size and number of elements provided do not match!");
		auto begin{ vec.begin() };
		auto end{ vec.end() };
		int i = 0;
		for (auto p{ begin }; p != end; ++p)
		{
			comps[i] = *p;
			i++;
		}
	};

	template<typename T, int size>
	T& Vector<T, size>::operator[](int index) {
		return comps[index];
	}

	template<typename T, int size>
	std::ostream& operator<< (std::ostream& out, const Vector<T, size>& vec) {
		out << "[" << vec.comps[0];
		for (size_t i = 1; i < vec.comps.size(); i++)
		{
			out << ", " << vec.comps[i];
		}
		out << "]";
		return out;
	}

	template<typename T, int size> 
	Vector<T, size> operator+ (const Vector<T, size>& a, const Vector<T, size>& b) {
		
		if (a.comps.size() != b.comps.size()) throw("Vector sizes do not match for addition!");
		std::array<T, size> result{};
		for (size_t i = 0; i < a.comps.size(); i++)
		{
			result[i] = a.comps[i] + b.comps[i];
		}
		return Vector<T, size>(result);
	}

	template<typename T, int size>
	Vector<T, size> operator- (const Vector<T, size>& a, const Vector<T, size>& b) {

		if (a.comps.size() != b.comps.size()) throw("Vector sizes do not match for subtraction!");
		std::array<T, size> result{};
		for (size_t i = 0; i < a.comps.size(); i++)
		{
			result[i] = a.comps[i] - b.comps[i];
		}
		return Vector<T, size>(result);
	}

	template<typename T, int size>
	Vector<T, size> operator* (T k, const Vector<T, size>& a) {

		std::array<T, size> result{};
		for (size_t i = 0; i < a.comps.size(); i++)
		{
			result[i] = k * a.comps[i];
		}
		return Vector<T, size>(result);
	}

	// Vector dot product function

	template<typename T, int size> 
	T vector_length(const Vector<T, size>& a) {
		T result{ a.comps[0] * a.comps[0] };
		for (size_t i = 1; i < a.comps.size(); i++)
		{
			result = result + (a.comps[i] * a.comps[i]);
		}
		return static_cast<T>( sqrt(result) );
	}

	template<typename T, int size>
	T dot_product(const Vector<T, size>& a, const Vector<T, size>& b) {
		
		if (a.comps.size() != b.comps.size()) throw("Vector sizes do not match for dot product!");
		T result{ a.comps[0] * b.comps[0] };
		for (size_t i = 1; i < a.comps.size(); i++)
		{
			result = result + (a.comps[i] * b.comps[i]);
		}
		return result;
	}

	template<typename T>
	Vector<T, 3> cross_product(const Vector<T, 3>& a, const Vector<T, 3>& b) {
		return Vector<T, 3>{ 
			(a.comps[1] * b.comps[2]) - (a.comps[2] * b.comps[1]),
			(a.comps[2] * b.comps[0]) - (a.comps[0] * b.comps[2]),
			(a.comps[0] * b.comps[1]) - (a.comps[1] * b.comps[0]) 
		};
	}


}

#endif
