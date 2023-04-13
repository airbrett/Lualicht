#include <string.h>
#include <cstdlib>

const wchar_t* char_to_wchar(const char* c)
{
	const size_t clen = strlen(c) + 1;
	wchar_t* wc = new wchar_t[clen];
	mbstowcs(wc, c, clen);

	return wc;
}