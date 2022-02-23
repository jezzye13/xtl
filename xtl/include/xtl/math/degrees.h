#pragma once

#include <xtl/strong_type.h>
#include <xtl/meta/operators.h>

namespace xtl
{
	class radians;

	class degrees
	{
		friend class radians;

	public:
		degrees() = default;
		~degrees() = default;

		degrees(float Value);
		degrees(const degrees& Degrees) = default;
		degrees(const radians& Radians);

		degrees& operator=(const degrees& Degrees) = default;
		degrees& operator=(const radians& Radians);
		degrees& operator=(float Value);

		operator float() const;

		degrees operator+(const degrees& Degrees) const;
		degrees operator+(float Value) const;

		degrees& operator+=(const degrees& Degrees);
		degrees& operator+=(float Value);

		degrees operator-(const degrees& Degrees) const;
		degrees operator-(float Value) const;

		degrees& operator-=(const degrees& Degrees);
		degrees& operator-=(float Value);


	public:
		//Note(Dragos): Should be public, no need for encapsulation when you'll only get the value
		float value;
	};
}