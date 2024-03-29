#ifndef RISA_PIXEL_HPP_
#define RISA_PIXEL_HPP_

#include <risa_gl/compile_time_assert.hpp>
#include <risa_gl/risa_types.hpp>

#include <ostream>
#include <cassert>

namespace risa_gl 
{
	/**
	 * 不透明度ピクセルクラス
	 */
	class opaque
	{
	public:
		enum {
			opaque_position = 0
		};

		typedef opaque self_type;

	private:
		byte y;

	public:
		opaque():
			y(255)
		{}

		opaque(int y_):
			y(y_ - 1)
		{
			assert(y_ > 0);
		}

		opaque(const opaque& source):
			y(source.y)
		{}

		~opaque()
		{}

		opaque& operator=(const opaque& source)
		{
			if (this != &source)
				this->y = source.y;

			return *this;
		}

		int get_opacity() const
		{
			return y + 1;
		}

		void set_opacity(int y_)
		{
			assert(y_ > 0);
			y = static_cast<byte>((y_ - 1) & 0xff);
		}
	};

	/**
	 * RGBAピクセルフォーマット構造体
	 */
	struct rgba
	{
		enum {
			red_position = 0,
			green_position = 1,
			blue_position = 2,
			alpha_position = 3
		};

		typedef rgba self_type;

		rgba():
			r(), g(), b(), a(255)
		{}

		rgba(byte r_, byte g_, byte b_, byte a_):
			r(r_), g(g_), b(b_), a(a_)
		{}

		rgba(const rgba& source):
			r(source.r), g(source.g), b(source.b), a(source.a)
		{}

		rgba& operator=(const rgba& rhs)
		{
			if (this != &rhs)
			{
				this->r = rhs.r;
				this->g = rhs.g;
				this->b = rhs.b;
				this->a = rhs.a;
			}

			return *this;
		}

		byte r;
		byte g;
		byte b;
		byte a;
	};

	/**
	 * AGBRピクセルフォーマット構造体
	 */
	struct abgr
	{
		enum {
			alpha_position = 0,
			blue_position = 1,
			green_position = 2,
			red_position = 3
		};

		typedef abgr self_type;

		abgr():
			a(255), b(), g(), r()
		{}

		abgr(byte r_, byte g_, byte b_, byte a_):
			a(a_), b(b_), g(g_), r(r_)
		{}

		abgr(const abgr& source):
			a(source.a), b(source.b), g(source.g), r(source.r)
		{}

		abgr& operator=(const abgr& rhs)
		{
			if (this != &rhs)
			{
				this->a = rhs.a;
				this->b = rhs.b;
				this->g = rhs.g;
				this->r = rhs.r;
			}

			return *this;
		}

		byte a;
		byte b;
		byte g;
		byte r;
	};

	/**
	 * ピクセルテンプレートクラス
	 */
	template <typename pixel_format>
	class pixel_type : private pixel_format
	{
	public:
		enum {
			red_position = pixel_format::red_position,
			green_position = pixel_format::green_position,
			blue_position = pixel_format::blue_position,
			alpha_position = pixel_format::alpha_position
		};

		typedef pixel_type self_type;
		typedef pixel_format base_type;

		pixel_type():
			pixel_format()
		{}

		pixel_type(byte r_, byte g_, byte b_, int a_ = 256):
			pixel_format(r_, g_, b_, a_ - 1)
		{}

		pixel_type(const pixel_type& source):
			pixel_format(source)
		{}

		~pixel_type()
		{}

		pixel_type& operator=(const pixel_type& source)
		{
			if (this != &source)
			{
				this->r = source.r;
				this->g = source.g;
				this->b = source.b;
				this->a = source.a;
			}

			return *this;
		}

		pixel_type operator*(const float factor) const
		{
			return pixel_type(static_cast<byte>(this->r * factor),
							  static_cast<byte>(this->g * factor),
							  static_cast<byte>(this->b * factor),
							  static_cast<byte>(this->a * factor));
		}

		byte get_red() const
		{
			return pixel_format::r;
		}

		void set_red(byte r_)
		{
			pixel_format::r = r_;
		}

		byte get_green() const
		{
			return pixel_format::g;
		}
		
		void set_green(byte g_)
		{
			pixel_format::g = g_;
		}

		byte get_blue() const
		{
			return pixel_format::b;
		}

		void set_blue(byte b_)
		{
			pixel_format::b = b_;
		}

		word get_alpha() const
		{
			return pixel_format::a + 1;
		}

		void set_alpha(word a_)
		{
			assert(a_ != 0);
			pixel_format::a = static_cast<byte>((a_ - 1) & 0xff);
		}

		uint32 get_bit_representation() const
		{
			return *reinterpret_cast<const uint32* const>(this);
		}

		void set_bit_representation(const uint32 value)
		{
			*reinterpret_cast<uint32* const>(this) = value;
		}
		
		bool operator==(const pixel_type& rhs) const
		{
			return
				this->r == rhs.r &&
				this->g == rhs.g &&
				this->b == rhs.b &&
				this->a == rhs.a;
		}

		bool operator!=(const pixel_type& rhs) const
		{
			return !this->operator==(rhs);
		}

		/**
		 * @todo 飽和加算に書き換え
		 */
		pixel_type& operator+=(const pixel_type& rhs)
		{
			this->r += rhs.r;
			this->g += rhs.g;
			this->b += rhs.b;
			this->a += rhs.a;
			return *this;
		}

		pixel_type operator+(const pixel_type& rhs) const
		{
			return pixel_type(*this) += rhs;
		}

		friend std::ostream& operator<<(
			std::ostream& out, const pixel_type<pixel_format>& self)
		{
			out << "pixel(" <<
				static_cast<unsigned short>(self.get_red()) <<	", " <<
				static_cast<unsigned short>(self.get_green()) << ", " <<
				static_cast<unsigned short>(self.get_blue()) << ", " <<
				static_cast<unsigned short>(self.get_alpha()) << ") ";
			return out;
		}
	};

	/**
	 * デフォルトピクセルクラスのエイリアス
	 */
	typedef pixel_type<rgba> pixel;

	/**
	 * ピクセルコンバータ
	 */
	template <typename SrcType, typename DestType>
	DestType pixel_convert(const SrcType& src)
	{
		return DestType(src.get_red(),
						src.get_green(),
						src.get_blue(),
						src.get_alpha());
	}
}

#endif /* RISA_PIXEL_HPP_ */
