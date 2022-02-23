#pragma once


#define ImplementAngleBinaryOperator(Operator, Lhs) \
Lhs Lhs::operator##Operator(const Lhs& angle) const \
{ \
	return Lhs(value Operator angle.value); \
} \
Lhs Lhs::operator##Operator(float angle) const \
{ \
	return Lhs(value Operator angle); \
} 

#define ImplementAngleAssignmentOperator(Operator, Lhs) \
Lhs& Lhs::operator##Operator(const Lhs& angle) \
{ \
	value Operator angle.value; \
	return *this; \
} \
Lhs& Lhs::operator##Operator(float angle) \
{ \
	value Operator angle; \
	return *this; \
} 