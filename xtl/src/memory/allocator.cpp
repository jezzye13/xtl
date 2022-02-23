#include <xtl/memory/allocator.h>


auto xtl::align(std::size_t Alignment, std::size_t Size, void* Ptr, std::size_t Space) -> decltype(Ptr)
{
	auto result = ((uintptr_t)Ptr + (Alignment - 1)) & ~(Alignment - 1);
	if (result + Size > (uintptr_t)Ptr + Space)
	{
		return nullptr;
	}

	return (char*)result;
}

void* xtl::stateless_allocator::alloc(size_t Size, size_t Align)
{
	void* data = m_alloc(Size, Align);

	return data;
}

void xtl::stateless_allocator::free(void* Ptr)
{
	m_free(Ptr);
}

xtl::malloc_allocator::malloc_allocator() :
	xtl::stateless_allocator(xtl::malloc_allocator::invoke_malloc,
		xtl::malloc_allocator::invoke_free)
{
}

void* xtl::malloc_allocator::invoke_malloc(size_t Size, size_t Align)
{
	return ::malloc(Size);
}

void xtl::malloc_allocator::invoke_free(void* Ptr)
{
	::free(Ptr);
}

