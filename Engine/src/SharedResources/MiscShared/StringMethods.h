#pragma once

namespace Engine::Utility
{
	//remove atoi error checking
	inline int FastATOI(const char* string)
	{
		int val = 0;
		while (*string)
		{
			val = val * 10 + (*string++ - '0');
		}
		return val;
	}
}
