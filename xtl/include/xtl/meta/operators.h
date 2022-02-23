#pragma once

namespace xtl
{
	//Note(Dragos): Should be somewhere else
	template <typename T>
	struct crtp
	{
		T& underlying() { return static_cast<T&>(*this); }
		T const& underlying() const { return static_cast<T const&>(*this); }
	};


	template <typename T>
	struct value_op_add : crtp<T>
	{
		T operator+(T const& Other)
		{ 
			return T(this->underlying().value + Other.value);
		}
	};

	template <typename T>
	struct value_op_addassign : crtp<T>
	{
		const T& operator+=(T const& Other)
		{
			this->underlying().value += Other.value;
			return *this;
		}
	};

	template <typename T>
	struct value_op_sub : crtp<T>
	{
		T operator-(T const& Other)
		{
			return T(this->underlying().value - other.value);
		}
	};

	template <typename T>
	struct value_op_subassign : crtp<T>
	{
		const T& operator-=(T const& Other)
		{
			this->underlying().value -= Other.value;
			return *this;
		}
	};

	template <typename T>
	struct value_op_div : crtp<T>
	{
		T operator/(T const& Other)
		{
			return T(this->underlying().value / Other.value);
		}
	};

	template <typename T>
	struct value_op_divassign : crtp<T>
	{
		const T& operator/=(T const& Other)
		{
			this->underlying().value /= Other.value;
			return *this;
		}
	};

	template <typename T>
	struct value_op_mul : crtp<T>
	{
		T operator*(T const& Other)
		{
			return T(this->underlying().value * Other.value);
		}
	};

	template <typename T>
	struct value_op_mulassign : crtp<T>
	{
		const T& operator*=(T const& Other)
		{
			this->underlying().value *= Other.value;
			return *this;
		}
	};

	template <typename T>
	struct value_op_valuecast : crtp<T>
	{
		operator auto()
		{
			return this->underlying().value;
		}
	};
}