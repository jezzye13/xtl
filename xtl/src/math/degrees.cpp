#include <xtl/math/degrees.h>
#include <xtl/math/radians.h>
#include <xtl/math/math.h>

#include "math/angleutils.h"

xtl::degrees::degrees(float Value) :
	value(Value)
{
}

xtl::degrees::degrees(const radians& Radians) :
	value(Radians.value * 360.f / (xtl::pi * 2.f))
{
}

xtl::degrees& xtl::degrees::operator=(const radians& Radians)
{
	value = Radians.value * 360.f / (xtl::pi * 2.f);
	return *this;
}

xtl::degrees& xtl::degrees::operator=(float Value)
{
	value = Value;
	return *this;
}

xtl::degrees::operator float() const
{
	return value;
}




ImplementAngleBinaryOperator(+, xtl::degrees)
ImplementAngleBinaryOperator(-, xtl::degrees)
ImplementAngleAssignmentOperator(+=, xtl::degrees)
ImplementAngleAssignmentOperator(-=, xtl::degrees)