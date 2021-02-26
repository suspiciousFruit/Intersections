#pragma once
#include <malloc.h>
#include <type_traits>


template <typename T>
class Array
{
	static_assert(std::is_trivially_destructible<T>::value, "Array: elements should have trivial destructor");
	static_assert(std::is_trivially_constructible<T>::value, "Trival type");
private:
	#define BASE_SIZE 8
	T* array_;
	size_t real_size_;
	size_t size_;
public:
	Array() : real_size_(0), size_(0), array_(nullptr)
	{ }

	Array(const std::initializer_list<T>& list) : real_size_(0), size_(0), array_(nullptr)
	{
		for (const auto& m : list)
			this->push_back(m);
	}
	
	Array(Array&& other) : array_(other.array_), size_(other.size)
	{
		other.array_ = nullptr;
		other.size = 0;
	}

	Array& operator= (Array&& other)
	{
		if (this != &other)
		{
			this->~Array();

			array_ = other.array_;
			size_ = other.size_;

			other.array_ = nullptr;
			other.size_ = 0;
		}

		return *this;
	}

	~Array()
	{
		free(array_);
	}

	void push_back(const T& value)
	{
		if (real_size_ == 0)
		{
			array_ = (T*)malloc(BASE_SIZE);
			real_size_ = BASE_SIZE;
		}
		else if (size_ >= real_size_)
		{
			array_ = (T*)realloc(array_, real_size_ * 2 * (sizeof(T)));

			real_size_ *= 2;
		}

		array_[size_++] = value;
	}

	inline const T* data() const { return array_; }
	inline T* data() { return array_; }
	inline size_t size() const { return size_; }
	inline void clear() { size_ = 0; }
};

