#pragma once
#include <stdint.h>
#include <xtl/string_op.h>


namespace xtl
{
	template <typename Char>
	class basic_string_view
	{
		const Char* m_str = nullptr;

	public:
		using char_t = Char;

	public:
		size_t length;
	public:
		basic_string_view(const char_t* src) :
			m_str(src)
		{
		}

		auto& operator=(const char_t* src)
		{
			m_str = src;
		}

		auto size() const
		{
			return length;
		}


		char_t* c_str() const
		{
			return m_str;
		}
	};

	using string_view = basic_string_view<char>;
}