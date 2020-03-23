#include "Sort.h"

void BubbleSort(int* data, int count)
{
	int tmp = 0;
	bool swap = false;
	for (int i = 0; i < count; ++i)
	{
		swap = false;
		for (int j = 1; j < count - i; ++j)
		{
			if (data[j] < data[j - 1])
			{
				swap = true;
				tmp = data[j];
				data[j] = data[j - 1];
				data[j - 1] = tmp;
			}
		}
		if (!swap) //如果没有交换，则直接返回，说明已经有序
		{
			return;
		}
	}
}

static void quick_sort(int* data, int p, int q);
static int partition(int* data, int p, int q);

void QuickSort(int* data, int count)
{
	quick_sort(data, 0, count - 1);
}

void quick_sort(int* data, int p, int q)
{
	if (p >= q)
	{
		return;
	}

	int r = partition(data, p, q);
	quick_sort(data, p, r - 1);
	quick_sort(data, r + 1, q);
}

 int partition(int* data, int p, int q)
{
	int l = p;
	int h = q;
	int s = data[l];
	while (l < h)
	{
		while (h > l && data[h] > s)
		{
			h--;
		}
		if (h > l)
		{
			data[l] = data[h];
			l++;
		}
		while (l < h && data[l] < s)
		{
			l++;
		}
		if (h > l)
		{
			data[h] = data[l];
			h--;
		}
	}
	data[h]	= s;
	return h;
}
