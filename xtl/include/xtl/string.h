#pragma once
#include <xtl/hash.h>
#include <type_traits>
#include <xtl/string_op.h>
#include <cassert>

namespace xtl
{

	template <typename Char, typename Allocator>
	class basic_string
	{
	public:
		using char_t = Char;

	public:
		basic_string(Allocator* allocator) :
			m_allocator(allocator)
		{
		}

		~basic_string()
		{
			cleanup();
		}

		auto* c_str() const
		{
			return m_str;
		}

		auto size() const
		{
			return m_length;
		}
		
		auto length() const
		{
			return m_length;
		}

		auto capacity() const
		{
			return m_capacity;
		}

		void assign(const char_t* str)
		{
			if (m_str)
			{
				m_allocator->free(m_str);
			}
			
			size_t size = strlen(str);
			if (size + 1 > m_capacity)
			{
				reserve(size * 2, false);
			}
			m_length = size;
			strcpy(m_str, str);
		}

		void assign(const basic_string& str)
		{
			if (m_str)
			{
				m_allocator->free(m_str);
			}
			if (str.m_length + 1 > m_capacity) //Note(Dragos): Null terminated string support should be dropped
			{
				reserve(size * 2, false);

			}
			m_length = size;
			strcpy(m_str, str.m_str);
		}


		bool reserve(size_t capacity, bool copy = true)
		{
			if (capacity > m_capacity)
			{
				auto* str = m_str;
				m_str = (char_t*)m_allocator->alloc(sizeof(char_t) * capacity, alignof(char_t));
				m_capacity = capacity;
				if (!m_str)
				{
					return false;
				}
				if (str && copy)
				{
					strcpy(m_str, str);
					cleanup();
				}
			}
			return true;
		}

		template <typename String>
		auto& operator<<(const String& str)
		{
			assert(size() + str.size() < capacity());
			strncpy(m_str + size(), str.c_str(), str.size());
			m_size += str.size();
			m_str[m_size] = 0;
		}

	private:
		void cleanup()
		{
			m_allocator->free(m_str);
		}

	private:
		Allocator* m_allocator = nullptr;
		char_t* m_str = nullptr;
		size_t m_length = 0;
		size_t m_capacity = 0;
	};

	template <typename Allocator>
	using string = basic_string<char, Allocator>;

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


	template <typename String>
		uint64_t hash(const String& key)
	{
		return byte_hash(key.c_str(), key.size() * sizeof(typename String::char_t));
	}

}