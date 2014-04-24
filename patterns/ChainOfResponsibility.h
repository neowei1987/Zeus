#ifndef ZUES_PATTERNS_CHAIN_OF_RESPONSIBILITY_H
#define ZUES_PATTERNS_CHAIN_OF_RESPONSIBILITY_H

#include <stdio.h>

//设计模式 责任链模式
//使多个对象都有机会处理请求，从而避免请求的发送者和接收者之间的耦合关系。将这些对象连成一条链，并沿着这条链传递该请求，直到有一个对象处理它为止。
namespace chain_of_responsibility 
{

class Handler 
{
public:
	Handler(Handler* successor = NULL) : m_pSuccessor(successor){}
	virtual void Request() = 0;
protected:
	Handler* m_pSuccessor;
};

class ConcreteHandler1 : public Handler
{
public:
	ConcreteHandler1(Handler* successor = NULL) : Handler(successor){}
	void Request()
	{
		printf("in handler1\n");
		if (m_pSuccessor)
		{
			m_pSuccessor->Request();
		}
		else
		{
			printf("Hanlder1: process by myself\n");
		}
	}
}; 

class ConcreteHandler2 : public Handler
{
public:
	ConcreteHandler2(Handler* successor = NULL) : Handler(successor){}
	void Request()
	{
		printf("in handler2\n");
		if (m_pSuccessor)
		{
			m_pSuccessor->Request();
		}
		else
		{
			printf("Hanlder2: process by myself\n");
		}
	}
};
};
#endif//ZUES_PATTERNS_CHAIN_OF_RESPONSIBILITY_H


