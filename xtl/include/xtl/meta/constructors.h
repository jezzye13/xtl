#pragma once

namespace xtl
{
	class non_copy_constructible
	{
		non_copy_constructible(const non_copy_constructible&) = delete;
	};

	class non_copy_assignable
	{
		non_copy_assignable& operator=(const non_copy_assignable&) = delete;
	};

	class non_move_constructible
	{
		non_move_constructible(non_copy_constructible&&) = delete;
	};

	class non_move_assignable
	{
		non_move_assignable& operator=(non_copy_assignable&&) = delete;
	};

	class non_copy :
		non_copy_constructible,
		non_copy_assignable
	{
	};

	class non_move :
		non_move_constructible,
		non_move_assignable
	{
	};
}