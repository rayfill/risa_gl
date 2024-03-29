#include <iostream>
#include <risa_gl/math/cosine.hpp>
#include <risa_gl/math/factorial.hpp>

 float get_cos(const float value)
{
	return risa_gl::math::cosine<float>::value(value);
}

inline int get_fact()
{
	return risa_gl::math::factorial<10>::value;
}

inline void check()
{
	std::cout << get_cos(static_cast<float>(3.1415926535897932384)) << std::endl;
	std::cout << get_fact() << std::endl;
}


int main()
{
	check();
	return 0;
}
