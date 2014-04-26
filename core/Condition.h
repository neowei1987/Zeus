#ifndef ZUES_CORE_CONDITION_H
#define ZUES_CORE_CONDITION_H

class TimeVal;

//条件变量
class ThreadCondition
{
public:
	ThreadCondition();
	virtual ~ThreadCondition();

	//等待
	void wait(TimeVal* timeout);
	//通知
	void notify();
	//通知所有
	void notifyAll();
};

#endif//ZUES_CORE_CONDITION_H


