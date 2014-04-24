#ifndef ZUES_PATTERNS_FLY_WEIGHT_H
#define ZUES_PATTERNS_FLY_WEIGHT_H

#include <stdio.h>
#include <map>

using std::map;

//设计模式 FlyWeight
//运用共享技术有效地支持大量细粒度的对象。
namespace flyweight 
{

class FlyWeight 
{
public:
	virtual void Run()
	{
		printf("fly weight[%p] run!\n", this);
	}
};

class FlyWeightFactory
{
public:
	FlyWeight* get(int key)
	{
		map<int, FlyWeight*>::iterator it = m_key2FlyWeight.find(key);
		if (it != m_key2FlyWeight.end())
		{
			return it->second;
		}
		else
		{
			FlyWeight* pNew = new FlyWeight();
			m_key2FlyWeight[key] = pNew;
			return pNew;
		}
	}

private:
	map<int, FlyWeight*> m_key2FlyWeight;
};

};
#endif//ZUES_PATTERNS_FLY_WEIGHT_H

