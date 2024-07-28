#pragma once


#define OUT
#define IN


/*
* CRASH
*/

#define ASSERT_CRASH(isOk)	\
{							\
	if(isOk)				\
	{						\
		return;				\
	}						\
							\
__int32* crash = nullptr;	\
	*crash = 0xDEADBEEF;	\
}							\