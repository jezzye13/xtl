#pragma once
#include <xtl/string.h>
#include <xtl/string_view.h>


namespace xtl
{

	namespace meta
	{
		template <typename T>
		struct is_string :
			public std::false_type
		{
		};

		template <typename T, typename Allocator>
		struct is_string<xtl::basic_string<T, Allocator>> :
			public std::true_type
		{
		};
	}


	template <typename String, typename =
		std::enable_if_t<meta::is_string<String>::value>>
		uint64_t hash<String>(const String& key)
	{
		return byte_hash(key.c_str(), key.size() * sizeof(typename String::char_t));
	}


	template <typename String>
	void strcpy(String* dst, const String* src)
	{
		strcpy(dst.c_str(), src.c_str());
	}

	template <typename String>
	void strncpy(String* dst, const String* src, size_t n)
	{
		strncpy(dst.c_str(), src.c_str(), n);
	}

	template <typename String>
	size_t strlen(const String* str)
	{
		return str.size();
	}


	template <typename String1, typename String2>
	bool operator==(const String1& lhs, const String2& rhs)
	{
		const auto* lptr = lhs.c_str();
		const auto* rptr = rhs.c_str();
		if (lptr == rptr)
		{
			if (rhs.length() == lhs.length())
			{
				return true;
			}
			return false;
		}
		if (!lptr || !rptr)
		{
			return false;
		}
		if (rhs.length() == lhs.length())
		{
			for (int i = 0; i < rhs.length(); i++)
			{
				if (lptr[i] != rptr[i])
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}

	template <typename String1, typename String2>
	bool operator!=(const String1& lhs, const String2& rhs)
	{
		return !(lhs == rhs);
	}

	template <typename String>
	basic_string_view<typename String::char_t> substr(const String& str, size_t first, size_t last)
	{
		assert(str.size() <= first + (last - first) && "Substring out of range");
		assert(str.c_str() && "Source string null");

		basic_string_view<typename String::char_t> result(str.c_str() + first);
		result.length = last - first;

		return result;
	}
}