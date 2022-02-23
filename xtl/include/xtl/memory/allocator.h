#pragma once
#include <memory>
#include <new>

namespace xtl
{

	template <typename T, typename... Args>
	T* emplace(void* dst, Args&&... args)
	{
		return new (dst) T(std::forward<Args>(args)...);
	}

	template <typename SmartPointer, typename T, typename... Args>
	T* emplace(SmartPointer& dst, Args&&... args)
	{
		emplace(dst.data(), std::forward<Args>(args)...);
	}

	auto align(std::size_t Alignment, std::size_t Size, void* Ptr, std::size_t Space) -> decltype(Ptr);

	template <size_t CAPACITY, size_t STORAGE_ALIGNMENT = alignof(std::max_align_t)>
	class auto_allocator
	{
	public:


	protected:
		alignas(STORAGE_ALIGNMENT) char m_storage[CAPACITY];

	public:
		static constexpr auto alignment()
		{
			return STORAGE_ALIGNMENT;
		}

		static auto capacity()
		{
			return CAPACITY;
		}


		void* data() const
		{
			return m_storage;
		}

		void* alloc(size_t Size, size_t Align = alignof(std::max_align_t))
		{
			void* data = align(Align, Size, m_storage, capacity());
			return data;
		}

		void free(void* Ptr)
		{

		}
	};

	class stateless_allocator
	{
	public:
		using alloc_fn_t = void* (*)(size_t, size_t);
		using free_fn_t = void(*)(void*);

		stateless_allocator(alloc_fn_t allocFn, free_fn_t freeFn) :
			m_alloc(allocFn),
			m_free(freeFn)
		{
		}

		void* alloc(size_t Size, size_t Align = alignof(std::max_align_t));

		void free(void* Ptr);


	private:
		alloc_fn_t m_alloc;
		free_fn_t m_free;
	};

	class malloc_allocator :
		public stateless_allocator
	{
	public:
		malloc_allocator();

	private:
		static void* invoke_malloc(size_t Size, size_t Align);
		static void invoke_free(void* Ptr);
	};

	template <typename InternalAllocator>
	class linear_allocator :
		public InternalAllocator
	{
	public:
		using internal_allocator_t = InternalAllocator;
	public:
		linear_allocator() = default;

		bool reserve(size_t Size, size_t Align = alignof(std::max_align_t))
		{
			m_start = InternalAllocator::alloc(Size, Align);
			if (m_start)
			{
				m_capacity = Size;
				m_usedSize = 0;
			}
			return m_start;
		}

		void* alloc(size_t Size, size_t Align = alignof(std::max_align_t))
		{
			auto next = (uintptr_t)m_start + m_usedSize;
			next = (decltype(next))align(Align, Size, m_start, m_capacity);
			if (!next)
			{
				if (!reserve(m_capacity * 2, alignof(std::max_align_t)))
				{
					return nullptr;
				}
			}

			return (void*)next;
		}

		void free(void* Ptr)
		{

		}

		void reset()
		{
			m_usedSize = 0;
		}

	private:
		void* m_start = nullptr;
		size_t m_capacity = 0;
		size_t m_usedSize = 0;
	};
}