#ifndef ZUES_PATTERNS_STATE_H
#define ZUES_PATTERNS_STATE_H

#include <stdio.h>

//设计模式 状态模式
//允许一个对象在其内部状态改变时改变它的行为。

namespace state
{

class Context;
class State 
{
public:
	virtual void handle(Context* context) = 0;
};

class StateA : public State
{
public:
	virtual void handle(Context* context);
}; 

class StateB : public State
{
public:
	virtual void handle(Context* context);
}; 


class Context 
{
public:
	Context(State* state)
	{
		m_pState = state;
	}

	void ChangeState(State* state)
	{
		if (m_pState)
		{
			delete m_pState;
		}
		m_pState = state;
	}

	void Request()
	{
		m_pState->handle(this);
	}
protected:
	State* m_pState;
};

void StateA::handle(Context* context)
{
	printf("do something in state A\n");
	//下一个状态是B
	context->ChangeState(new StateB());
}

void StateB::handle(Context* context)
{
	printf("do something in state B\n");
	//下一个状态是A
	context->ChangeState(new StateA());
}

};
#endif//ZUES_PATTERNS_STATE_H

