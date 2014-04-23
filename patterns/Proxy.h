#ifndef ZUES_PATTERNS_PROXY_H
#define ZUES_PATTERNS_PROXY_H

#include <stdio.h>

//设计模 代理模式
//为其他对象提供一种代理以控制对这个对象的访问。

namespace proxy
{

class Subject 
{
public:
	virtual void Request() = 0;
};

class RealSubject: public Subject
{
public:
	virtual void Request()
	{
		printf("do work by real subjct\n");
	}
};

class SubjectProxy : public Subject
{
public:
	SubjectProxy()
	{
		m_pRealSubject = NULL;
	}
	void Request()
	{
		if (!m_pRealSubject)
		{
			m_pRealSubject = new RealSubject();
		}
		m_pRealSubject->Request();
	}
protected:
	RealSubject* m_pRealSubject;	
};

};
#endif//ZUES_PATTERNS_PROXY_H

