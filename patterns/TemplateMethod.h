#ifndef ZUES_PATTERNS_TEMPLATE_METHOD_H
#define ZUES_PATTERNS_TEMPLATE_METHOD_H

#include <stdio.h>

//设计模式 模版方法
//定义一个操作中的算法的骨架，而将一些步骤延迟到子类中。TemplateMethod 使得子类可以不改变一个算法的结构即可重定义该算法的某些特定步骤。
namespace template_method 
{
	
class People
{
public:
	virtual void doWork()
	{
		DoA();
		DoB();
	}
	virtual void DoA() = 0;
	virtual void DoB() = 0;
};

class MondayPeople : public People
{
public:
	void DoA()
	{
		printf("DoA in monday\n");
	}
	void DoB()
	{
		printf("DoB in monday\n");
	}
};

class SunDayPeople : public People
{
public:
	void DoA()
	{
		printf("DoA in sunday\n");
	}
	void DoB()
	{
		printf("DoB in sunday\n");
	}
};

};
#endif//ZUES_PATTERNS_TEMPLATE_METHOD_H

