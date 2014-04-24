#ifndef ZUES_PATTERNS_MEMENTO_H
#define ZUES_PATTERNS_MEMENTO_H

#include <stdio.h>
#include <string>

using std::string;

//设计模式 备忘录模式
//在不破坏封装性的前提下，捕获一个对象的内部状态，并在该对象之外保存这个状态。这样以后就可将该对象恢复到原先保存的状态。
namespace memento 
{

class Memento
{
	friend class Originator;
private:
	Memento(const string& sState)
	{
		m_sState = sState;
	}

	string m_sState;
};

class Originator 
{
public:
	void setState(const string& sState)
	{
		m_sState = sState;
	}

	void printState()
	{
		printf("Originator state: %s\n", m_sState.c_str());
	}

	Memento* createMemento()
	{
		return new Memento(m_sState);
	}

	void recoverState(Memento* memento)
	{
		m_sState = memento->m_sState;
	}
protected:
	string m_sState;
};

};
#endif//ZUES_PATTERNS_MEMENTO_H

