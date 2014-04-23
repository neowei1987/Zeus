#ifndef ZUES_DEFINES_H
#define ZUES_DEFINES_H

#include <linux/types.h>

#define COUNT_OF(arr) (sizeof(arr) / sizeof(arr[0]))

//判断一个数是不是2的幂次方
//#define IS_POW_2(x) ((x >> 1 << 1) == x) 这个算法错误的，只能判断一个数是否偶数
#define IS_POW_2(x) (!(x & (x - 1)))

inline int POW(int a, int x)
{
	if (x == 1)	
	   	return a; 
	else if (x == 0)
		return 1;
	else
	{
		int t = POW(a, x >> 1);
		//printf("%d^%d=%d\n", a, x >> 1, t);
		t *= t;
		if (!IS_POW_2(x))
		{
			t *= a;
		}
		return t;
	}
}

inline int LOG2(int x)
{
	if (x == 1)
	{
		return 0;
	}
	else
	{
		return 1 + LOG2(x >> 1);
	}

}
//向上取2的幂次方，3=>4, 17=>32等
#define UP_TO_POW_2(x)((IS_POW_2(x)) ? x : (POW(2, LOG2(x) + 1)))

#endif//ZUES_DEFINES_H


