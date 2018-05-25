#include "color.hpp"

sdk::Color sdk::Color::Black(0, 0, 0, 255);
sdk::Color sdk::Color::White(255, 255, 255, 255);
sdk::Color sdk::Color::Red(255, 0, 0, 255);
sdk::Color sdk::Color::Green(0, 128, 0, 255);
sdk::Color sdk::Color::Blue(0, 0, 255, 255);

sdk::Color::Color()
{
	*((int *)this) = 0;
}

sdk::Color::Color(int _r, int _g, int _b)
{
	SetColor(_r, _g, _b, 255);
}

sdk::Color::Color(int _r, int _g, int _b, int _a)
{
	SetColor(_r, _g, _b, _a);
}

void sdk::Color::SetRawColor(int color32)
{
	*((int *)this) = color32;
}

int sdk::Color::GetRawColor() const
{
	return *((int *)this);
}

void sdk::Color::SetColor(int _r, int _g, int _b, int _a)
{
	CColor[0] = (unsigned char)_r;
	CColor[1] = (unsigned char)_g;
	CColor[2] = (unsigned char)_b;
	CColor[3] = (unsigned char)_a;
}

void sdk::Color::SetColor(float _r, float _g, float _b, float _a)
{
	CColor[0] = static_cast<unsigned char>(_r * 255.0f);
	CColor[1] = static_cast<unsigned char>(_g * 255.0f);
	CColor[2] = static_cast<unsigned char>(_b * 255.0f);
	CColor[3] = static_cast<unsigned char>(_a * 255.0f);
}

void sdk::Color::GetColor(int &_r, int &_g, int &_b, int &_a) const
{
	_r = CColor[0];
	_g = CColor[1];
	_b = CColor[2];
	_a = CColor[3];
}

bool sdk::Color::operator== (const sdk::Color &rhs) const
{
	return (*((int *)this) == *((int *)&rhs));
}

bool sdk::Color::operator!= (const sdk::Color &rhs) const
{
	return !(operator==(rhs));
}

sdk::Color& sdk::Color::operator=(const sdk::Color &rhs)
{
	SetRawColor(rhs.GetRawColor());

	return *this;
}