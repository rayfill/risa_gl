#ifndef RISA_PS_COLOR_BURN_BLEND_HPP_
#define RISA_PS_COLOR_BURN_BLEND_HPP_

#include <operators/primitive/blend.hpp>
#include <operators/primitive/alpha_factor.hpp>
#include <operators/building_blocks.hpp>
#include <operators/alpha_blend.hpp>

namespace risa_gl
{
	namespace operators
	{
		class color_burn_blend_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				color_burn_function<source_selector,
						destination_selector>,
				identity_alpha_factor,
				identity_alpha_factor,
				not_calculate_policy>
			color_burn_blend_operator_type;

			color_burn_blend_operator_type blender;
			
		public:
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

		class color_burn_blend_save_source_alpha_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				color_burn_function<source_selector,
						destination_selector>,
				identity_alpha_factor,
				identity_alpha_factor,
				alpha_calculate_policy<source_alpha_getter> >
			color_burn_blend_save_source_alpha_operator_type;

			color_burn_blend_save_source_alpha_operator_type blender;
			
		public:
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

		/**
		 * PS互換焼き込みカラーブレンディング(alphaは破壊)
		 */
		// {{{ ps_color_burn_blend_operator
		class ps_color_burn_blend_operator
		{
		private:
			typedef photoshop_blend<
				color_burn_blend_save_source_alpha_operator,
				alpha_blend_operator>
			ps_color_burn_blend_operator_type;
			ps_color_burn_blend_operator_type blender;
		public:
			ps_color_burn_blend_operator():
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
		 * PS互換焼き込みカラーブレンディング(alphaはdestinationを保存)
		 */
		// {{{ ps_color_burn_blend_save_destination_alpha_operator
		class ps_color_burn_blend_save_destination_alpha_operator
		{
		private:
			typedef photoshop_blend<
				color_burn_blend_save_source_alpha_operator,
				alpha_blend_save_destination_alpha_operator>
			ps_color_burn_blend_operator_type;
			ps_color_burn_blend_operator_type blender;
		public:
			ps_color_burn_blend_save_destination_alpha_operator():
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

#endif /* RISA_PS_COLOR_BURN_BLEND_HPP_ */