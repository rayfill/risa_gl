#ifndef RISA_STATIC_ARRAY_HPP_
#define RISA_STATIC_ARRAY_HPP_
#include <stdexcept>

namespace risa_gl
{
	template <typename BaseType, int Length>
	class static_array
	{
	public:
		typedef BaseType value_type;
		typedef value_type& reference_type;
		typedef const value_type& const_reference_type;

		typedef value_type* pointer_type;
		typedef value_type const * const_pointer_type;

		typedef pointer_type iterator;
		typedef const_pointer_type const_iterator;

		typedef size_t size_type;
		
		value_type elements[Length];

		const_reference_type operator[](int offset) const
		{
			return elements[offset];
		}

		reference_type operator[](int offset)
		{
			return elements[offset];
		}

		const reference_type at(int offset) const
		{
			if (offset < 0 || offset >= Length)
				throw std::out_of_range("offset is out of range.");

			return elements[offset];
		}

		reference_type at(int offset)
		{
			if (offset < 0 || offset >= Length)
				throw std::out_of_range("offset is out of range.");

			return elements[offset];
		}

		iterator begin()
		{
			return elements;
		}

		iterator end()
		{
			return elements + Length;
		}

		const_iterator begin() const
		{
			return elements;
		}

		const_iterator end() const
		{
			return elements + Length;
		}

		size_type size() const
		{
			return Length;
		}

		bool operator==(const static_array& rhs) const
		{
			for (size_type offset = 0; offset != Length; ++offset)
				if (this->operator[](offset) != rhs[offset])
					return false;

			return true;
		}

		bool operator!=(const static_array& rhs) const
		{
			return !this->operator==(rhs);
		}
	};
}

#endif /* RISA_STATIC_ARRAY_HPP_ */