#ifndef TOOLSH
#define TOOLSH

#include <ClanLib/core.h>

template <class T>
class Tools
{
public:
	static inline int sign(T n)
	{
		return (n >= 0) ? 1 : -1;
	}

	static inline T abs(T n)
	{
		return (n < 0) ? -n : n;
	}

	static inline T minimum(T n1, T n2)
	{
		return (n1 < n2) ? n1 : n2;
	}

	static inline T maximum(T n1, T n2)
	{
		return (n1 > n2) ? n1 : n2;
	}

	static inline double pi()
	{
		return 3.14159265358979323846;
	}
};

#endif
