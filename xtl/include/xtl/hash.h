#pragma once
#include <stdint.h>

namespace xtl
{
	template <typename Key>
	uint64_t hash(const Key& key)
	{
		return 0;
	}

	uint64_t byte_hash(void* ptr, size_t size);
}