#ifndef RISA_ITERATOR_TRAITS_HPP_
#define RISA_ITERATOR_TRAITS_HPP_

#include "iterator.hpp"

namespace risa_gl
{
	/**
	 * 対象ポインタがアライメント境界に整列されているかを調べる
	 * @param alignment 境界バイト数
	 * @param ptr 調べる対象ポインタ
	 * @return 整列されていればtrue
	 */
	template <typename pixel_t, size_t alignment>
	class iterator_adapter
	{
	public:
		typedef pixel_t pixel_type;
		typedef sequential_iterator<pixel_type> iterator_type;
		typedef sequential_iterator<const pixel_type> const_iterator_type;
		typedef alignment_iterator<pixel_type, alignment> fragments_type;
		typedef alignment_iterator<const pixel_type, alignment> const_fragments_type;

		static bool is_alignment(const void* ptr)
		{
			return (reinterpret_cast<size_t>(ptr) % alignment) == 0;
		}

		static iterator_type to_sequential(fragments_type& itor)
		{
			return iterator_type(&*itor);
		}

		static fragments_type to_fragments(iterator_type& itor)
		{
			return fragments_type(&*itor);
		}
	};
};
#endif /* RISA_ITERATOR_TRAITS_HPP_ */
