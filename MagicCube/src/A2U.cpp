
#include <locale.h>
#include <stdlib.h>
#include "MagicCube.h"

wchar_t* A2U(const char* in)
{
	//ASCII to Unicode
	wchar_t *out = new wchar_t[sizeof(wchar_t)*strlen(in)];
	mbstowcs(out, in, strlen(in));

	//return
	return out;
}