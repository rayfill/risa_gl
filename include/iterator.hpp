#ifndef RISA_ITERATOR_HPP_
#define RISA_ITERATOR_HPP_

#include "risa_types.hpp"
#include "exception.hpp"
#include <cassert>

namespace risa_gl
{
	template <typename ValueType>
	class sequential_iterator
	{
	public:
		typedef ValueType  value_type;
		typedef ValueType* pointer_type;
		typedef ValueType& reference_type;

	private:
		pointer_type itor;

	public:
		sequential_iterator():
			itor()
		{}

		sequential_iterator(pointer_type pointer):
			itor(pointer)
		{}
			
		sequential_iterator(const sequential_iterator& source):
			itor(source.itor)
		{}

		~sequential_iterator()
		{}

		reference_type operator*()
		{
			return *itor;
		}

		const reference_type operator*() const
		{
			return *itor;
		}

		pointer_type operator->()
		{
			return itor;
		}

		const pointer_type operator->() const
		{
			return itor;
		}

		sequential_iterator& operator++()
		{
			++itor;
			return *this;
		}

		sequential_iterator operator++(int)
		{
			sequential_iterator result(*this);
			++itor;
			return result;
		}

		sequential_iterator& operator--()
		{
			--itor;
			return *this;
		}

		sequential_iterator operator--(int)
		{
			sequential_iterator result(*this);
			--itor;
			return *this;
		}

		sequential_iterator operator+(const int difference)
		{
			itor += difference;
			return *this;
		}

		sequential_iterator operator-(const int difference)
		{
			itor -= difference;
			return *this;
		}

		bool operator==(const sequential_iterator& rhs) const
		{
			return this->itor == rhs.itor;
		}

		bool operator!=(const sequential_iterator& rhs) const
		{
			return !this->operator==(rhs);
		}

	};

	template <typename ValueType, size_t FragmentsSize>
	class alignment_iterator
	{
	public:
		enum {
			fragments_size = FragmentsSize,
		};

		typedef ValueType value_type;
		typedef ValueType* pointer_type;
		typedef ValueType& reference_type;

	private:
		pointer_type itor;

	public:
		alignment_iterator():
			itor()
		{}

		alignment_iterator(pointer_type pointer):
			itor(pointer)
		{
			if (reinterpret_cast<size_t>(pointer) % fragments_size)
				throw alignment_error();
		}
			
		alignment_iterator(const alignment_iterator& source):
			itor(source.itor)
		{}

		~alignment_iterator()
		{}

		reference_type operator*()
		{
			return *itor;
		}

		const reference_type operator*() const
		{
			return *itor;
		}

		pointer_type operator->()
		{
			return itor;
		}

		const pointer_type operator->() const
		{
			return itor;
		}

		alignment_iterator& operator++()
		{
			itor = reinterpret_cast<pointer_type>(
				reinterpret_cast<byte*>(itor) + fragments_size);
			return *this;
		}

		alignment_iterator operator++(int)
		{
			alignment_iterator result(*this);
			++itor;
			return result;
		}

		alignment_iterator& operator--()
		{
			itor = reinterpret_cast<pointer_type>(
				reinterpret_cast<byte*>(itor) - fragments_size);
			return *this;
		}

		alignment_iterator operator--(int)
		{
			alignment_iterator result(*this);
			--itor;
			return result;
		}

		bool operator==(const alignment_iterator& rhs) const
		{
			return this->itor == rhs.itor;
		}

		bool operator!=(const alignment_iterator& rhs) const
		{
			return !this->operator==(rhs);
		}
	};
};

#endif /* RISA_ITERATOR_HPP_ */
