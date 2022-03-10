#pragma once
#include <cassert>
#include <utility>

namespace xtl
{
	//call it a packed array
	template <typename T, typename Allocator>
	class sparse_set
	{
	public:
		using allocator_t = Allocator;
		using internal_t = T;

		//0 is null handle.
		struct handle
		{
			size_t id = 0;
		};

	public:
		sparse_set(Allocator* allocator) :
			m_allocator(allocator)
		{

		}

		bool reserve(size_t size)
		{
			m_array = m_allocator->alloc(size * sizeof(registry_entry_t), alignof(registry_entry_t));
			m_capacity = size;
			if (!m_array)
			{
				return false;
			}
			return true;
		}

		~sparse_set()
		{
			m_allocator->free(m_array);
		}

		template <typename T1, typename... Args>
		handle emplace(Args&&... args)
		{
			assert(sizeof(T1) <= sizeof(T) && alignof(T1) <= alignof(T) && "Incompatible type emplace in sparse_set");
	
			handle loc;

			for (int i = 0; i < m_capacity; i++)
			{
				
			}

			return loc;
		}

		bool remove(handle key, T& found_value)
		{
			const auto h = hash(key);
			for (int i = 0; i < m_capacity; i++)
			{
				const auto index = (h + i) % m_capacity;
				const auto& entry = m_table[index];
				if (entry.state == hash_entry_t::states::unoccupied)
				{
					return false;
				}
				else if (entry.hash == h && entry.key == key)
				{
					entry.state = hash_entry_t::states::dead;
					found_value = entry.value;
					return true;
				}
			}

			return false;
		}

	private:
		struct registry_entry_t
		{
			size_t index;
			handle handle;
			T value;
		};

	private:
		Allocator* m_allocator;
		registry_entry_t* m_array = nullptr;
		size_t m_load = 0;
		size_t m_capacity = 0;
	};
}