#ifndef ZUES_PATTERNS_STRATEGY_H
#define ZUES_PATTERNS_STRATEGY_H

#include <stdio.h>

//设计模式 策略模式
//定义一系列的算法，把它们一个个封装起来，并且使它们可相互替换。本模式使得算法可独立于使用它的客户而变化。

namespace strategy
{

class Strategy
{
public:
	virtual void doJob() = 0;
};

class MyStrategy : public Strategy
{
public:
	virtual void doJob()
	{
		printf("do my job\n");
	}
}; 

class Context 
{
public:
	Context(Strategy* strategy)
	{
	   	m_pStrategy = strategy;
	}

	void doJob()
	{
		m_pStrategy->doJob();
	}
protected:
	Strategy* m_pStrategy;
};

};
#endif//ZUES_PATTERNS_STRATEGY_H

