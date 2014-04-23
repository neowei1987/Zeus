#ifndef ZUES_PATTERNS_COMPOSITE_H
#define ZUES_PATTERNS_COMPOSITE_H

#include <stdio.h>
#include <vector>

using std::vector;

//设计模 组合模式 
//将对象组合成树形结构以表示“部分-整体”的层次结构。Composite使得用户对单个对象和组合对象的使用具有一致性。
namespace composite
{

class Compontent
{
public:
	virtual void add(Compontent* compontent) = 0;
	virtual void remove(Compontent* compontent)	= 0;
	virtual Compontent* getChild(int i)	= 0;
	virtual void doWork() = 0;
};

class Leaf : public Compontent 
{
public:
	virtual void add(Compontent* compontent) {};
	virtual void remove(Compontent* compontent)	{};
	virtual Compontent* getChild(int i)	{return NULL;};

	virtual void doWork()
	{
		printf("do work by leaf\n");
	}
};

class Composite : public Compontent
{
public:
	virtual void add(Compontent* compontent)
	{
		m_vctCompontent.push_back(compontent);
	}

	virtual void remove(Compontent* compontent)	
	{
	}

	virtual Compontent* getChild(int i)
	{
		return m_vctCompontent[i];
	}

	virtual void doWork()
	{
		for (int i = 0; i < m_vctCompontent.size(); ++i)
		{
			m_vctCompontent[i]->doWork();
		}
	}
private:
	vector<Compontent*> m_vctCompontent;
};

};
#endif//ZUES_PATTERNS_COMPOSITE_H

