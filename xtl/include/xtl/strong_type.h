#pragma once

namespace xtl
{
	template <typename T, 
		typename Unique, 
		template <typename> typename... Skills>
	class strong_type :
		public Skills<strong_type<T, Unique, Skills...>>...
	{
	public:
		using value_t = T;

	public:
		value_t value;

	public:
		strong_type() = default;
		strong_type(const strong_type& Other) = default;
		strong_type(const T& Value) :
			value(Value)
		{
		}

		strong_type& operator=(const strong_type& Other) = default;
		strong_type& operator=(const T& Value)
		{
			value = Value;
			return *this;
		}
	};
}