#ifndef ZUES_PATTERNS_DOCORATOR_H
#define ZUES_PATTERNS_DOCORATOR_H

#include <stdio.h>

//设计模 装饰者模式
//动态地给一个对象添加一些额外的职责。就增加功能来说，Decorator 模式相比生成子类更为灵活。

namespace decorator
{

//抽象组件
class Compontent
{
public:
	virtual void doWork() = 0;
};

//具体组件
class ConcreateCompontent: public Compontent 
{
public:
	virtual void doWork()
	{
		printf("do work by concreate compontent\n");
	}
};

//装饰者基类
class Decorator : public Compontent
{
public:
	Decorator(Compontent* compontent)
	{
		m_pCompontent = compontent;
	}
protected:
	Compontent* m_pCompontent;	
};

class OneDecorator : public Decorator
{
public:
	OneDecorator(Compontent* compontent) : Decorator(compontent){}
	void doWork()
	{
		printf("this is done by one!\n");
		m_pCompontent->doWork();
	}
};

class  TwoDecorator : public Decorator
{
public:
	TwoDecorator(Compontent* compontent) : Decorator(compontent){}
	void doWork()
	{
		m_pCompontent->doWork();
		printf("this is done by two!\n");
	}

};
};
#endif//ZUES_PATTERNS_DOCORATOR_H

