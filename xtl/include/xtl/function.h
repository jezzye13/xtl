#pragma once

#include <iostream>
#include <variant>
#include <random>
#include <memory>
#include <type_traits>
#include <vector>
#include <stack>
#include <array>
#include <queue>
#include <cstdlib>
#include <functional>
#include <xtl/memory/allocator.h>

namespace xtl
{
	template <typename T>
	class function;

	template <typename Return, typename... Args>
	class function<Return(Args...)>
	{
		template <typename m_T>
		friend class function;


	private:
		template <typename Other>
		struct is_this : std::false_type {};

		template <typename FnType>
		struct is_this<function<FnType>> : std::true_type {};


		using invoke_fn_t = Return(*)(char*, Args&&...);
		using construct_fn_t = void(*)(char*, const char*);
		using destroy_fn_t = void(*)(char*);
	public:
		using return_t = Return;
		using internal_fn_t = Return(Args...);

	private:
		invoke_fn_t m_invoke = nullptr;
		construct_fn_t m_construct = nullptr;
		destroy_fn_t m_destroy = nullptr;

		char* m_data = nullptr;

		size_t m_dataSize = 0;
		//size_t m_align = STORAGE_ALIGNMENT;
		//size_t m_emptySpace = 0;

	private:
		template <typename Functor>
		static Return invoke_fn(Functor* fn, Args&&... args)
		{
			return (*fn)(std::forward<Args>(args)...);
		}

		template <typename Functor>
		static void construct_fn(Functor* constructDst, Functor* constructSrc)
		{
			new (constructDst) Functor(*constructSrc);
		}

		template <typename Functor>
		static void destroy_fn(Functor* fn)
		{
			fn->~Functor();
		}

	public:
		function() = default;

		template <typename Allocator>
		function& assign(const function& other, Allocator& allocator)
		{
			static_assert(other.capacity() <= this->capacity(), "Function assignment stack size mismatch");

			if (m_invoke)
			{
				this->destruct(m_data);
			}
			m_invoke = other.m_invoke;
			m_construct = other.m_construct;
			m_destroy = other.m_destroy;
			m_dataSize = other.m_dataSize;

			if (m_invoke)
			{
				/*if (m_align < other.m_align)
				{
					m_data = align(other.m_align, other.m_size, this->m_storage, storage_size());
					m_align = other.m_align;
				}*/
				allocator.free(m_data);
				m_data = (char*)allocator.alloc(other.m_size, other.m_align);
				m_construct(m_data, other.m_data);
			}

			return *this;
		}

		template<typename Functor, typename Allocator>
		function& assign(Functor fn, Allocator& allocator)
		{
			constexpr size_t requiredAlign = alignof(Functor);
			if (m_invoke)
			{
				m_destroy(m_data);
			}

			m_invoke = reinterpret_cast<invoke_fn_t>(invoke_fn<Functor>);
			m_construct = reinterpret_cast<construct_fn_t>(construct_fn<Functor>);
			m_destroy = reinterpret_cast<destroy_fn_t>(destroy_fn<Functor>);
			m_dataSize = sizeof(Functor);


			/*if (m_align < alignof(Functor))
			{
				m_data = align(alignof(Functor), sizeof(Functor), this->m_storage, storage_size());
				m_align = alignof(Functor);
				m_emptySpace = m_data - this->m_storage;
			}*/
			allocator.free(m_data);
			m_data = (char*)allocator.alloc(sizeof(Functor), alignof(Functor));
			m_construct(m_data, reinterpret_cast<char*>(&fn));
			return *this;
		}


		~function()
		{
			if (m_invoke)
			{
				m_destroy(m_data);
			}

		}

		Return operator()(Args&&... args)
		{
			m_invoke(m_data, std::forward<Args>(args)...);
		}
	};
}
