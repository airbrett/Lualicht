#pragma once

template<typename T>
T ToInteger(const double v)
{
	return static_cast<T>(v);
}

auto const ToS32 = &ToInteger<irr::s32>;

const wchar_t* char_to_wchar(const char* c);
