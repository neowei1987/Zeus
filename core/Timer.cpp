#include "Timer.h"
#include "utility/Tools.h"

TimerNode::TimerNode(int iTimerId, int iCallType, int iTimeInterval, void* pHandler)
{
	m_iTimerId = iTimerId;
	m_iCallType = iCallType;
	m_iTimeInterval = iTimeInterval;
	m_fnHandler = (TIMER_HANDLER)pHandler;
	m_iNextTime = 0;
}

bool TimerNode::isLessThan(int iNextTime) 
{
	return m_iNextTime < iNextTime;
}

void TimerNode::updateNextTime()
{
}

Timer::Timer() 
{
	m_iNextTimerId = 0;
	//启动一个线程
	Thread::Start();
}

Timer::~Timer()
{
	//m_bExit;
	
	//结束一个线程	
	Thread::Kill();
}

int Timer::Run()
{
	while (true)	
	{
		int iSleepMicroSeconds = OnTimeout();
		if (iSleepMicroSeconds > 0)
		{
			zues::Sleep(iSleepMicroSeconds);		
		}
	}
}

int Timer::AddTimer(int iMicroSecond, TIMER_HANDLER fnHandler, bool bRepeat)
{
}

ListTimer::ListTimer() : Timer()
{
	m_pNodeList = new DoubleList();
	DoubleListInit(m_pNodeList);
}

ListTimer::~ListTimer()
{
}

int ListTimer::AddTimer(int iMicroSecond, TIMER_HANDLER fnHandler, bool bRepeat)
{
	int iTimerId = NewTimerId();	
	ListTimerNode* pNode = NULL;//new ListTimerNode();
	//遍历链表，找到插入点
	DoubleList* pInsertPoint = m_pNodeList;
	for_each_entry_at_list(entry, m_pNodeList)
	{
		ListTimerNode* pNode = CONTAINER_PTR(entry, ListTimerNode, list);
		if (pNode)
		{
		}
	}
//	DoubleListInsertAfter();k
}

int ListTimer::AddTimer(int iMicroSecond, ITimerHandler* pHandler, bool bRepeat)
{
}

void ListTimer::RemovieTimer(int iTimerId)
{

}
