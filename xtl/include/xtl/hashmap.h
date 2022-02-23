#pragma once
#include <stdint.h>
#include <xtl/hash.h>

namespace xtl
{
	


	template <typename Key, typename Value, typename Allocator>
	class hashmap
	{
	public:
		using hash_entry_t = hash_entry<Key, Value>;

	public:
		hashmap(Allocator* allocator) :
			m_allocator(allocator)
		{
			reserve(10);
		}

		void insert(const Key& key, const Value& value)
		{
			const auto h = hash(key);

			for (int i = 0; i < m_capacity; i++)
			{
				const auto index = (h + i) % m_capacity;
				
				if (!m_table[index].state != hash_entry_t::states::occupied)
				{
					hash_entry_t entry;
					entry.hash = h;
					entry.key = key;
					entry.value = value;
					entry.state = hash_entry_t::states::occupied;
					m_table[index] = entry;
					m_load++;
					break;
				}
				else if (m_table[index].hash == h && m_table[index].key == key)
				{
					entry.value = value;
					break;
				}
			}
		}

		bool find(const Key& key, Value& found_value)
		{
			const auto h = hash(key);
			for (int i = 0; i < m_capacity; i++)
			{
				const auto index = (h + i) % m_capacity;
				const auto& entry = m_table[index];

				if (!entry.occupied)
				{
					return false;
				}
				else if (entry.hash == h && entry.key == key)
				{
					found_value = entry.value;
					return true;
				}
			}

			return false;
		}

		bool remove(const Key& key, Value& found_value)
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

		~hashmap()
		{
			m_allocator->free(m_table);
		}

		//finish
		void reserve(size_t entries)
		{
			m_allocator->alloc(sizeof(hash_entry_t) * entries, alignog(hash_entry_t));
			m_capacity = entries;
		}

	private:
		template <typename Key, typename Value>
		struct hash_entry
		{
			enum states
			{
				unoccupied,
				occupied,
				dead
			} state;
			uint64_t hash;
			Key key;
			Value value;
		};

	private:
		Allocator* m_allocator;
		hash_entry_t* m_table;
		size_t m_load = 0;
		size_t m_capacity = 0;
	};
}