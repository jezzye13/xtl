#include <xtl/math/radians.h>
#include <xtl/math/degrees.h>
#include <xtl/math/math.h>

#include "math/angleutils.h"

xtl::radians::radians(float Value) :
	value(Value)
{
}

xtl::radians::radians(const radians& Radians) :
	value(Radians.value)
{
}

xtl::radians::radians(const degrees& Degrees) :
	value(Degrees.value * (xtl::pi * 2.f) / 360.f)
{
}

xtl::radians::operator float() const
{
	return value;
}

xtl::radians& xtl::radians::operator=(const radians& Radians)
{
	value = Radians.value;
	return *this;
}

xtl::radians& xtl::radians::operator=(const degrees& Degrees)
{
	value = Degrees.value * (xtl::pi * 2.f) / 360.f;
	return *this;
}

xtl::radians& xtl::radians::operator=(float Value)
{
	value = Value;
	return *this;
}

ImplementAngleBinaryOperator(+, xtl::radians)
ImplementAngleBinaryOperator(-, xtl::radians)
ImplementAngleAssignmentOperator(+=, xtl::radians)
ImplementAngleAssignmentOperator(-=, xtl::radians)

