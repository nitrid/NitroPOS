
// stdafx.cpp : source file that includes just the standard includes
// ePos.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"


void LongToBcd(int pSrc, uint8 *pOutDest , int pDestLen)
{
	int i, high, low;

	for (i = pDestLen - 1; i >= 0; i--)
	{
		low  = (int)(pSrc % 10);
		pSrc /= 10;
		high = (int)(pSrc % 10);
		pSrc /= 10;
		pOutDest[i] = (char)((high << 4) | low);
	}
}
