#ifndef ZUES_PATTERNS_ADAPT_H
#define ZUES_PATTERNS_ADAPT_H

#include <stdio.h>

//设计模式 适配器模式
//将一个类的接口转换成客户希望的另外一个接口。Adapt 模式使得原本由于接口不兼容而不能一起工作的那些类可以一起工作。
namespace adapt 
{
//需要被Adapt的类
class Target
{
public:
	virtual void Request() = 0;
};

//与被Adapt对象提供不兼容接口的类
class Adaptee
{
public:
	void callRequest()
	{
		printf("i m called by face of TARGET!!\n");
	}
};

//基于继承的适配器
class ClassAdapter : public Target, public Adaptee
{
public:
	void Request()
	{
		//调用不兼容的接口
		Adaptee::callRequest();
	}
};

//基于组合（对象）的适配器
class ObjectAdapter : public Target
{
public:
	ObjectAdapter(Adaptee* adaptee)
	{
		m_pAdaptee = adaptee;
	}

	void Request()
	{
		m_pAdaptee->callRequest();
	}
private:
	Adaptee* m_pAdaptee;
};

};
#endif//ZUES_PATTERNS_ADAPT_H

