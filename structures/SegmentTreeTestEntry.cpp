#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "SegmentTree.h"

struct Segment
{
	Segment()
	{
	}
	Segment(int start, int len)
	{
		start_ = start;
		end_ = start_ + len;
	}
	int len()
	{
		return end_ - start_;
	}
	void set(int start, int len)
	{
		start_ = start;
		end_ = start_ + len;
	}
	int start_;
	int end_;

};

int segment_compare(const void* p1, const void* p2)
{
	Segment* s1 = (Segment*)p1;
	Segment* s2 = (Segment*)p2;
	if (s1->start_ < s2->start_)
	{
		return -1;
	}
	else
	{
		return (s1->start_ > s2->start_ ? 1 : 0);
	}
}

int SegmentTreeTestEntry(int argc, char* argv[])
{
	srand(time(NULL));

	int count = atoi(argv[1]);
	int i = 0;
	Segment* segments = new Segment[count];
	/*
	segments[0].set(1, 2);
	segments[1].set(0, 2);
	segments[2].set(4, 2);
	segments[3].set(7, 1);
	segments[4].set(6, 3);
	*/
	int min_start = 10000;
	int max_end = -1;
	while (i < count)
	{
		segments[i].set(rand() % 10, rand() % 10);
		if (segments[i].start_ < min_start)	
		{
			min_start = segments[i].start_;
		}
		if (segments[i].end_ > max_end)
		{
			max_end = segments[i].end_;
		}
		i++;
	}

	printf("min: %d, max: %d\n", min_start, max_end);	
	SegmentTree tree(min_start, max_end);
	i = 0;
	while (i < count)
	{
		tree.insert(segments[i].start_, segments[i].end_);
		i++;
	}
	printf("segment tree count: %d\n", tree.count());

	qsort(segments, count, sizeof(Segment), segment_compare);

	int sum = 0;
	int start = segments[0].start_;
	int j = 0;
	i = 0;
	while (true)
	{
		j = i + 1;
		while (j < count && (segments[j].end_ <= segments[i].end_ && segments[j].start_ <= segments[i].end_))//后面的块包含在前一块内
		{
			//printf("contains\n");
			j++;
		}
		if (j == count) //必须在此退出
		{
			sum += (segments[i].end_ - start);   //一段结束
			break;
		}
		if (segments[j].start_ > segments[i].end_) //第二块完全在第一块前面
		{
			//printf("total pre\n");
			sum += (segments[i].end_ - start);   //一段结束
			//printf("total sum: %d\n", sum);
			start = segments[j].start_;
		}
		else
		{
			//printf("overlap\n");
		}
		//else 交叉
		i = j;
	}

	i = 0;
	while (i < count)
	{
		//printf("%d-%d\n", segments[i].start_, segments[i].end_);
		i++;
	}

	printf("total sum: %d\n", sum);
}
