#pragma once

#include <stdint.h>
#include <utility>
#include <cassert>c

namespace xtl
{
	namespace meta
	{
		template <typename... Types>
		struct sizeof_largest
		{

		};

		template <typename Type1, typename... Types>
		struct sizeof_largest<Type1, Types...>
		{
			static constexpr size_t value = sizeof(Type1) < alignof_types<Types...>::value ? alignof_types<Types...>::value : sizeof(Type1);
		};

		template <typename Type1, typename Type2>
		struct sizeof_largest<Type1, Type2>
		{
			static constexpr size_t value = sizeof(Type1) < sizeof(Type2) ? sizeof(Type2) : sizeof(Type1);
		};

		template <typename Type1>
		struct sizeof_largest<Type1>
		{
			static constexpr size_t value = sizeof(Type1);
		};

		template <typename... Types>
		struct sizeof_types
		{
			static constexpr size_t value = 0;
		};

		template <typename Type1, typename... Types>
		struct sizeof_types<Type1, Types...>
		{
			static constexpr size_t value = sizeof(Type) + sizeof_types<Types...>::value;
		};

		template <typename... Types>
		struct alignof_types
		{

		};

		template <typename Type1, typename... Types>
		struct alignof_types<Type1, Types...>
		{
			static constexpr size_t value = alignof(Type1) < alignof_types<Types...>::value ? alignof_types<Types...>::value : alignof(Type1);
		};

		template <typename Type1, typename Type2>
		struct alignof_types<Type1, Type2>
		{
			static constexpr size_t value = alignof(Type1) < alignof(Type2) ? alignof(Type2) : alignof(Type1);
		};

		template <typename Type1>
		struct alignof_types<Type1>
		{
			static constexpr size_t value = alignof(Type1);
		};


		template<typename Same, typename First, typename... More>
		struct is_any {
			static constexpr bool value = std::is_same<Same, First>::value ||
				is_any<First, More...>::value;
		};

		template<typename Same, typename First>
		struct is_any<Same, First>
		{
			static constexpr bool value = std::is_same<Same, First>::value;
		};


	}


	template <typename Tag, typename... Types>
	class tagged_union
	{
	public:
		using tag_t = Tag;
		static constexpr size_t union_size = meta::sizeof_largest<Types...>::value * 8;
		static constexpr size_t union_align = meta::alignof_types<Types...>::value;

	private:
		char alignas(union_align) m_buffer[union_size]{};
		Tag m_tag;

	public:
		
	public:
		auto tag() const
		{
			return m_tag;
		}
		
		template <typename T>
		T& as()
		{
			return *reinterpret_cast<T*>(m_buffer);
		}

		template <typename T>
		T& as() const
		{
			return *reinterpret_cast<T*>(m_buffer);
		}

		template <typename T, typename... Args>
		T& emplace(Tag tag, Args&&... args)
		{
			//this fails?
			//static_assert(meta::is_any<T, Types...>::value && "Attempting to emplace a type that is not part of the tagged union declaration");
			new (m_buffer) T(std::forward<Args>(args)...);
			this->m_tag = tag;
			return as<T>();
		}
	};
}