#pragma once

#include <xtl/strong_type.h>
#include <xtl/meta/operators.h>

namespace xtl
{
	class degrees;

	class radians 
	{
		friend class degrees;

	public:
		radians() = default;
		~radians() = default;

		radians(float Value);
		radians(const radians& Radians);
		radians(const degrees& Degrees);

		operator float() const;

		radians& operator=(const radians& Radians);
		radians& operator=(const degrees& Degrees);
		radians& operator=(float Value);

		radians operator+(const radians& Degrees) const;
		radians operator+(float Value) const;

		radians& operator+=(const radians& Degrees);
		radians& operator+=(float Value);

		radians operator-(const radians& Degrees) const;
		radians operator-(float Value) const;

		radians& operator-=(const radians& Degrees);
		radians& operator-=(float Value);



	public:
		//Note(Dragos): Should be public, no need for encapsulation when you'll only get the value
		float value;
	};
}