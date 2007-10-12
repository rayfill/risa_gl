#ifndef RISA_PS_SCREEN_BLEND_HPP_
#define RISA_PS_SCREEN_BLEND_HPP_

#include <operators/primitive/blend.hpp>
#include <operators/primitive/alpha_factor.hpp>
#include <operators/building_blocks.hpp>
#include <operators/screen_blend.hpp>
#include <operators/alpha_blend.hpp>

namespace risa_gl
{
	namespace operators
	{
		/**
		 * PS互換積色ブレンディング(alphaは破壊)
		 */
		// {{{ ps_screen_blend_operator
		class ps_screen_blend_operator
		{
		private:
			typedef photoshop_blend<screen_blend_save_source_alpha_operator,
									alpha_blend_operator>
			ps_screen_blend_operator_type;
			ps_screen_blend_operator_type blender;
		public:
			ps_screen_blend_operator():
				blender()
			{}

			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t dest,
							result_itor_t result) const
			{
				blender(src, dest, result);
			}
		};
		// }}}

		/**
		 * PS互換積色ブレンディング(alphaはdestinationを保存)
		 */
		// {{{ ps_screen_blend_save_destination_alpha_operator
		class ps_screen_blend_save_destination_alpha_operator
		{
		private:
			typedef photoshop_blend<
				screen_blend_save_source_alpha_operator,
				alpha_blend_save_destination_alpha_operator>
			ps_screen_blend_operator_type;
			ps_screen_blend_operator_type blender;
		public:
			ps_screen_blend_save_destination_alpha_operator():
				blender()
			{}

			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t dest,
							result_itor_t result) const
			{
				blender(src, dest, result);
			}
		};
		// }}}
	}
}

#endif /* RISA_PS_SCREEN_BLEND_HPP_ */
