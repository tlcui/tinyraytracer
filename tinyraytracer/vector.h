#pragma once
#ifndef VECTOR_H_
#define VECTOR_H_

#include<array>
#include<cmath>
#include<cassert>
#include<iostream>

template <typename T, std::size_t N>
class Vector final
{
public:
	static_assert(
		N > 0,
		"Size of static-sized vector should be greater than zero.");
	static_assert(
		std::is_floating_point<T>::value,
		"Vector only can be instantiated with floating point types");

	//! Construct a vector with zeros.
	Vector();

	//! Construct vector instance with parameters.
	template <typename... Params>
	explicit Vector(Params... params);

	//! Set all elements to  s.
	void set(const T& s);

	//! Construct vector instance with initializer list.
	template <typename U>
	Vector(const std::initializer_list<U>& lst);

	//! Set vector instance with initializer list.
	template <typename U>
	void set(const std::initializer_list<U>& lst);

	//! Copy constructor.
	Vector(const Vector& other);

	//! Swaps the content of the vector with \p other vector.
	void swap(Vector& other);

	//! Sets all elements to zero.
	void setZero();

	//! Returns the size of the vector.
	constexpr size_t size() const;

	//! Returns the const reference to the \p i -th element.
	const T& operator[](size_t i) const;

	//! Returns the reference to the \p i -th element.
	T& operator[](size_t i);

	//! Returns the raw pointer to the vector data.
	T* data();

	//! Returns the const raw pointer to the vector data.
	const T* const data() const;

	//! Set vector instance with initializer list.
	template <typename U>
	Vector& operator=(const std::initializer_list<U>& lst);

	//! Set vector with expression template.
	Vector& operator=(const Vector& other);

	Vector operator+(const Vector& other) const;
	Vector operator-(const Vector& other) const;
	
	Vector& operator+=(const Vector& other);
	Vector& operator-=(const Vector& other);

	//! Compute dot product.
	T dot(const Vector& v) const;
	
	Vector operator+(const T& s) const;
	Vector operator-(const T& s) const;
	Vector operator*(const T& s) const;
	Vector operator/(const T& s) const;

	Vector& operator+=(const T& s);
	Vector& operator-=(const T& s);
	Vector& operator*=(const T& s);
	Vector& operator/=(const T& s);

	//! Returns true if other is the same as this vector.
	template <typename E>
	bool operator==(const E& other) const;

	//! Returns true if other is not the same as this vector.
	template <typename E>
	bool operator!=(const E& other) const;

	//! Compute norm and square of norm.
	T norm() const;
	T norm_squared() const;

	//! Normalizes this vector.
	void normalize();

	//! Return normalized vector.
	Vector normalized() const;

	//! Returns true if other is similar to this vector.
	template <typename E>
	bool is_similar(const E& other,
		T epsilon = std::numeric_limits<T>::epsilon()) const;

private:
	std::array<T, N> _elements;

	template <typename... Params>
	void setAt(size_t i, T v, Params... params);
	
	void setAt(size_t i, T v);
};




template<typename T, std::size_t N>
inline Vector<T, N>::Vector()
{
	std::cout << "construct with 0\n";
	for (auto& elem : _elements)
	{
		elem = static_cast<T>(0);
	}
}

template<typename T, std::size_t N>
template<typename ...Params>
inline Vector<T, N>::Vector(Params ...params)
{
	static_assert(sizeof...(params) == N, "Invalid number of parameters.");

	setAt(0, params...);
}

template<typename T, std::size_t N>
inline void Vector<T, N>::set(const T& s)
{
	_elements.fill(s);
}


template<typename T, std::size_t N>
template<typename U>
inline Vector<T, N>::Vector(const std::initializer_list<U>& lst)
{
	std::cout << "construct with initializer list\n";
	set(lst);
}

template<typename T, std::size_t N>
template<typename U>
inline void Vector<T, N>::set(const std::initializer_list<U>& lst)
{
	assert(lst.size() >= N);

	size_t i = 0;
	for (const auto& inputElem : lst) 
	{
		_elements[i] = static_cast<T>(inputElem);
		++i;
	}
}

template<typename T, std::size_t N>
inline Vector<T, N>::Vector(const Vector& other): _elements(other._elements)
{
}

template<typename T, std::size_t N>
inline void Vector<T, N>::swap(Vector& other)
{
	std::swap(other._elements, _elements);
}

template<typename T, std::size_t N>
inline void Vector<T, N>::setZero()
{
	_elements.fill(0);
}

template<typename T, std::size_t N>
inline constexpr size_t Vector<T, N>::size() const
{
	return N;
}

template<typename T, std::size_t N>
inline const T& Vector<T, N>::operator[](size_t i) const
{
	// TODO: 在此处插入 return 语句
	return _elements[i];
}

template<typename T, std::size_t N>
inline T& Vector<T, N>::operator[](size_t i)
{
	// TODO: 在此处插入 return 语句
	return _elements[i];
}

template<typename T, std::size_t N>
inline T* Vector<T, N>::data()
{
	return _elements.data();
}

template<typename T, std::size_t N>
inline const T* const Vector<T, N>::data() const
{
	return _elements.data();
}

template<typename T, std::size_t N>
template<typename U>
inline Vector<T, N>& Vector<T, N>::operator=(const std::initializer_list<U>& lst)
{
	// TODO: 在此处插入 return 语句
	assert(lst.size() == N);

	set(lst);
	return *this;
}

template<typename T, std::size_t N>
inline Vector<T,N>& Vector<T, N>::operator=(const Vector& other)
{
	// TODO: 在此处插入 return 语句
	assert(other.size() == N);

	for (std::size_t i=0; i<N; i++)
	{
		_elements[i] = other._elements[i];
	}
	return *this;
}

template<typename T, std::size_t N>
inline Vector<T,N> Vector<T, N>::operator+(const Vector& other) const
{
	assert(other.size() == N);
	
	Vector result(other);
	for (std::size_t i =0; i < N; i++)
	{
		result._elements[i] += _elements[i];
	}

	return result;
}

template<typename T, std::size_t N>
inline Vector<T,N> Vector<T, N>::operator-(const Vector& other) const
{
	assert(other.size() == N);

	Vector result(other);
	for (std::size_t i = 0; i < N; i++)
	{
		result._elements[i] -= _elements[i];
	}

	return result;
}

template<typename T, std::size_t N>
inline Vector<T,N>& Vector<T, N>::operator+=(const Vector& other)
{
	// TODO: 在此处插入 return 语句
	assert(other.size() == N);

	for (std::size_t i = 0; i < N; ++i)
	{
		_elements[i] += other[i];
	}

	return *this;
}

template<typename T, std::size_t N>
inline Vector<T,N>& Vector<T, N>::operator-=(const Vector& other)
{
	// TODO: 在此处插入 return 语句
	assert(other.size() == N);

	for (std::size_t i = 0; i < N; ++i)
	{
		_elements[i] -= other[i];
	}

	return *this;
}

template<typename T, std::size_t N>
inline T Vector<T, N>::dot(const Vector& v) const
{
	assert(v.size() == N);

	T result = 0;
	for (std::size_t i = 0; i < N; i++)
	{
		result += (_elements[i] * v[i]);
	}

	return result;
}

template<typename T, std::size_t N>
inline Vector<T,N> Vector<T, N>::operator+(const T& s) const
{
	Vector result(*this);
	for (std::size_t i = 0; i < N; i++)
	{
		result[i] += s;
	}

	return result;
}

template<typename T, std::size_t N>
inline Vector<T,N> Vector<T, N>::operator-(const T& s) const
{
	Vector result(*this);
	for (std::size_t i = 0; i < N; i++)
	{
		result[i] -= s;
	}

	return result;
}

template<typename T, std::size_t N>
inline Vector<T,N> Vector<T, N>::operator*(const T& s) const
{
	Vector result(*this);
	for (std::size_t i = 0; i < N; i++)
	{
		result[i] *= s;
	}

	return result;
}

template<typename T, std::size_t N>
inline Vector<T,N> Vector<T, N>::operator/(const T& s) const
{
	Vector result(*this);
	for (std::size_t i = 0; i < N; i++)
	{
		result[i] /= s;
	}

	return result;
}

template<typename T, std::size_t N>
inline Vector<T,N>& Vector<T, N>::operator+=(const T& s)
{
	// TODO: 在此处插入 return 语句
	for (std::size_t i = 0; i < N; ++i)
	{
		_elements[i] += s;
	}

	return *this;
}

template<typename T, std::size_t N>
inline Vector<T,N>& Vector<T, N>::operator-=(const T& s)
{
	// TODO: 在此处插入 return 语句
	for (std::size_t i = 0; i < N; ++i)
	{
		_elements[i] -= s;
	}

	return *this;
}

template<typename T, std::size_t N>
inline Vector<T,N>& Vector<T, N>::operator*=(const T& s)
{
	// TODO: 在此处插入 return 语句
	for (std::size_t i = 0; i < N; ++i)
	{
		_elements[i] *= s;
	}

	return *this;
}

template<typename T, std::size_t N>
inline Vector<T,N>& Vector<T, N>::operator/=(const T& s)
{
	// TODO: 在此处插入 return 语句
	for (std::size_t i = 0; i < N; ++i)
	{
		_elements[i] /= s;
	}

	return *this;
}

template<typename T, std::size_t N>
inline T Vector<T, N>::norm() const
{
	return std::sqrt(norm_squared());
}

template<typename T, std::size_t N>
inline T Vector<T, N>::norm_squared() const
{
	return dot(*this);
}

template<typename T, std::size_t N>
inline void Vector<T, N>::normalize()
{
	(*this) /= std::sqrt(norm_squared());
}

template<typename T, std::size_t N>
inline Vector<T,N> Vector<T, N>::normalized() const
{
	return Vector(*this) / this->norm();
}

template<typename T, std::size_t N>
inline void Vector<T, N>::setAt(size_t i, T v)
{
	_elements[i] = v;
}

template<typename T, std::size_t N>
template<typename E>
inline bool Vector<T, N>::operator==(const E& other) const
{
	if (N != other.size()) 
	{
		return false;
	}

	for (size_t i = 0; i < N; ++i) 
	{
		if (_elements[i] != other[i])
		{
			return false;
		}
	}
	return true;
}

template<typename T, std::size_t N>
template<typename E>
inline bool Vector<T, N>::operator!=(const E& other) const
{
	return !((*this)==other);
}

template<typename T, std::size_t N>
template<typename E>
inline bool Vector<T, N>::is_similar(const E& other, T epsilon) const
{
	if (N != other.size()) 
	{
		return false;
	}

	for (size_t i = 0; i < N; ++i) 
	{
		if (std::fabs(_elements[i] - other[i]) > epsilon) {
			return false;
		}
	}
	return true;
}


template<typename T, std::size_t N>
template<typename ...Params>
inline void Vector<T, N>::setAt(size_t i, T v, Params ...params)
{
	_elements[i] = v;
	setAt(i + 1, params...);
}

template<typename T, std::size_t N, typename E>
inline Vector<T, N> operator+(const E& s, const Vector<T,N>& v)
{
	return v + static_cast<T>(s);
}

template<typename T, std::size_t N, typename E>
inline Vector<T, N> operator-(const T& s, const Vector<T, N>& v)
{
	return v - static_cast<T>(s);
}

template<typename T, std::size_t N,typename E>
inline Vector<T, N> operator*(const T& s, const Vector<T, N>& v)
{
	return v * static_cast<T>(s);
}

template<typename T, std::size_t N, typename E>
inline Vector<T, N> operator/(const T& s, const Vector<T, N>& v)
{
	return v / static_cast<T>(s);
}


#endif