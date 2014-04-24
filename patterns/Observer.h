#ifndef ZUES_PATTERNS_OBSERVER_H
#define ZUES_PATTERNS_OBSERVER_H

#include <stdio.h>
#include <list>

using std::list;

//设计模式 观察者模式
//定义对象间的一种一对多的依赖关系，当一个对象的状态发生改变时，所有依赖于它的对象都得到通知并被自动更新。
namespace observer 
{

class Observer;
class Subject 
{
public:
	Subject()
	{
		m_iState  = 0;
	}

	virtual void addObserver(Observer* observer) = 0;
	virtual void deleteObserver(Observer* observer) = 0;
	virtual void notify() = 0;

	virtual int getState(){return m_iState;}
	virtual void setState(int iState){m_iState = iState;}

protected:
	int m_iState;
};

class ConcreteSubject : public Subject 
{
public:
	virtual void addObserver(Observer* observer)
	{
		m_lstObserver.push_back(observer);
	}
	virtual void deleteObserver(Observer* observer)
	{

	}
	virtual void notify();
private:
	list<Observer*> m_lstObserver;
};


class Observer
{
public:
	virtual void update(Subject* subject) = 0;
};

void ConcreteSubject::notify()
{
	list<Observer*>::iterator it = m_lstObserver.begin();
	while (it != m_lstObserver.end())
	{
		//在这儿调用此函数会产生编译错误
		//理论上应该定义在cpp文件里面。这样子就不会出错了
		(*it)->update(this);
		++it;
	}
}

class OneObserver : public Observer 
{
public:
	virtual void update(Subject* subject)
	{
		printf("one: subject state[%d]\n", subject->getState());
	}
};

class TwoObserver : public Observer 
{
public:
	virtual void update(Subject* subject)
	{
		printf("two: subject state[%d]\n", subject->getState());
	}
};

};
#endif//ZUES_PATTERNS_OBSERVER_H

