#ifndef ZUES_STRUCTURES_HEAP_H
#define ZUES_STRUCTURES_HEAP_H

/*
 * 堆有如下作用：
 * （1）排序
 * （2）优先队列
 * （3）TOP K 最大堆，最小堆
 * */

#include <vector>
using std::vector;

template <class T>
class Heap
{
public:
	Heap(){}
	virtual ~Heap(){}

	//添加一个元素
	virtual void push(const T& elem)
	{
		//压入新元素
		container_.push_back(elem);
		//自底向上调整堆
		int i = container_.size() - 1;
		int p = 0;
		while (i > 0)
		{
			p = parent(i);
			if (!check_and_swap(i, p))
			{
				break;
			}
			else
			{
				i = p;		
			}
		}
		//dump();	
	}

	//获取top元素
	const T& top()
	{
		return container_[0];
	}
	
	//弹出top元素
	void pop()
	{
		if (!empty())	
		{
			int i = container_.size() - 1;
			container_[0] = container_[i]; //复制到堆顶
			container_.pop_back(); //移除最后一个元素
			int p = 0;
			//自顶向下调整堆
			while (true)
			{
				//如果两个孩子，取最大
				//如果一个孩子，则就他比
				//如果没有孩子，则退出
				if (((i = get_max_child(p)) < 0) 
					|| !check_and_swap(i, p))
				{
					break;
				}
				else 
				{
					p = i;
				}
			}
		}
		//dump();	
	}

	//是否为空
	bool empty()
	{
		return !container_.size();
	}
	
	int size() {return container_.size();}
protected:
	virtual int element_compare(const T& item1, const T& item2)
	{
		return item1 - item2;
	}

	void dump()
	{
		printf("#");
		for (int i = 0; i < container_.size(); ++i)
		{
			printf("%d\t", container_[i]);
		}
		printf("\n");
	}
	void swap(int t1, int t2)
	{
		T temp = container_[t1];
		container_[t1] = container_[t2];
		container_[t2] = temp;
	}

	int get_max_child(int p)
	{
		//判断有没有左孩子，
		int left = left_child(p);
		if (left >= container_.size())
		{
			return -1;
		}
		int right  = right_child(p);
		if (right >= container_.size())
		{
			return left;
		}

		if (element_compare(container_[left], container_[right]) >= 0) 
		{
			return left;
		}
		else
		{
			return right;
		}
	}

	bool check_and_swap(int c, int p)
	{
		if (element_compare(container_[c], container_[p]) > 0) //如果c > p 则交换
		{
			swap(c, p);
			return true;
		}
		else
		{
			return false;
		}
	}
	int parent(int i)
	{
		return (i - 1) >> 1;
	}
	int left_child(int p)
	{
		return (p << 1) + 1;
	}
	int right_child(int p)
	{
		return (p << 1) + 2;
	}
protected:
	vector<T> container_;
};


template <class T>
class MinHeap : public Heap<T>
{
protected:
	virtual int element_compare(const T& item1, const T& item2)
	{
		return item2 - item1;
	}

};

//最小的K个，则利用最大堆
template <class T, class HEAP>
class TopKContainer : public HEAP
{
public:
	TopKContainer(int k) : k_(k){}
	virtual ~TopKContainer(){}

	void push(const T& item)
	{
		if (HEAP::size() < k_)
		{
			HEAP::push(item);
		}
		else
		{
			const T& m = HEAP::top();
			if (HEAP::element_compare(item, m) < 0)//比最大的元素小，则把最大元素pop掉，然后push进该元素
			{
				HEAP::pop();
				HEAP::push(item);
			}
		   	//如果比最大的还要大，则略过此元素
		}
	}
private:
	int k_;
};
#endif//ZUES_STRUCTURES_HEAP_H
