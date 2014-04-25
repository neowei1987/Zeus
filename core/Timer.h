#ifndef ZUES_CORE_TIMER_H
#define ZUES_CORE_TIMER_H

#include <map>
#include "structures/List.h"
#include "thread.h"

using std::map;

//回调过程
typedef void (*TIMER_HANDLER)(void*);

//回调接口
class ITimerHandler 
{
public:
	virtual void Process(int iTimerId) = 0;
};

class TimerNode
{
public: 
	TimerNode(int iTimerId, int iCallType, int iTimeInterval, void* pHandler);
	bool isLessThan(int iNextTime);
	void updateNextTime();
	int m_iTimerId; //计时器id
	int m_iCallType; //调用类型
	long m_iTimeInterval; //调用时间间隔
	long m_iNextTime; //下次调用时间
	union 
	{
		TIMER_HANDLER m_fnHandler;
		ITimerHandler* m_pHandler;
	};
};

class Timer : public Thread
{
public:
	Timer();
	virtual ~Timer();

	//用户调用
	virtual int AddTimer(int iMicroSecond, TIMER_HANDLER fnHandler, bool bRepeat = true) = 0;
	virtual int AddTimer(int iMicroSecond, ITimerHandler* pHandler, bool bRepeat = true) = 0;
	virtual void RemovieTimer(int iTimerId) = 0;

	virtual int OnTimeout() = 0;

	virtual int Run();	
protected:
	int NewTimerId() {return m_iNextTimerId++;}
private:
	int m_iNextTimerId;
};

//基于链表实现的定时器
class ListTimerNode : public TimerNode
{
public:
	ListTimerNode(int iTimerId, int iCallType, int iTimeInterval, void* pHandler) : TimerNode(iTimerId, iCallType, iTimeInterval, pHandler) {}
	DoubleList list;
};

class ListTimer : public Timer
{
public:
	ListTimer();
	~ListTimer();
	virtual int AddTimer(int iMicroSecond, TIMER_HANDLER fnHandler, bool bRepeat = true);
	virtual int AddTimer(int iMicroSecond, ITimerHandler* pHandler, bool bRepeat = true);
	virtual void RemovieTimer(int iTimerId);
protected:
private:
	DoubleList* m_pNodeList;
};

//基于堆实现的定时器
class HeapTimer : public Timer
{
public:
	virtual int AddTimer(int iMicroSecond, TIMER_HANDLER fnHandler, bool bRepeat = true);
	virtual int AddTimer(int iMicroSecond, ITimerHandler* pHandler, bool bRepeat = true);
	virtual void RemovieTimer(int iTimerId);
};

//基于时间轮实现的定时器
class TimeWheelTimer : public Timer
{
public:
	virtual int AddTimer(int iMicroSecond, TIMER_HANDLER fnHandler, bool bRepeat = true);
	virtual int AddTimer(int iMicroSecond, ITimerHandler* pHandler, bool bRepeat = true);
	virtual void RemovieTimer(int iTimerId);
};

#endif//ZUES_CORE_TIMER_H

