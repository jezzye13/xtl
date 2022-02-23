#include <xtl/hash.h>

uint64_t xtl::byte_hash(void* ptr, size_t size)
{
	const uint64_t fnv_offset_basis = 0xcbf29ce484222325ull;
	const uint64_t fnv_prime = 0x00000100000001B3ull;

	uint64_t result = fnv_offset_basis;

	for (uint8_t* crt = (uint8_t*)ptr; crt < (uint8_t*)ptr + size; crt++)
	{
		result *= fnv_prime;
		result ^= *crt;
	}

	return result;
}
