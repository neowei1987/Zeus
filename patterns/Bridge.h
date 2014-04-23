#ifndef ZUES_PATTERNS_BRIDGE_H
#define ZUES_PATTERNS_BRIDGE_H

#include <stdio.h>

//设计模式 桥模式 
//将抽象部分与它的实现部分分离，使它们都可以独立地变化。
namespace bridge
{


class LoggerImp
{
public:
	virtual void doWork() = 0;
};

class LoggerImpByA : public LoggerImp
{
public:
	virtual void doWork()
	{
		printf("do work by A\n");
	}
};

class LoggerImpByB : public LoggerImp
{
public:
	virtual void doWork()
	{
		printf("do work by B\n");
	}
};

class Logger
{
public:
	Logger(LoggerImp* pImp)
	{
		m_pImp = pImp;
	}
	void doWork()
	{
		m_pImp->doWork();
	}
private:
	LoggerImp* m_pImp;
};

};
#endif//ZUES_PATTERNS_BRIDGE_H

