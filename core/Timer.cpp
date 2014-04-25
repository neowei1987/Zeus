#include <sys/time.h>
#include "Timer.h"
#include "utility/Tools.h"

enum CALLBACK_TYPE
{
	CALLBACK_TYPE_FUNC,
	CALLBACK_TYPE_CLASS,
};
TimerNode::TimerNode(int iTimerId, int iCallType, int iTimeInterval, void* pHandler, bool bRepeat)
{
	m_iTimerId = iTimerId;
	m_bRepeat = bRepeat;
	m_iCallType = iCallType;
	m_iTimeInterval = iTimeInterval;
	m_fnHandler = (TIMER_HANDLER)pHandler;
}

bool TimerNode::operator >= (TimerNode& other)
{
	return m_tvNextTime >= other.m_tvNextTime;
}

void TimerNode::updateNextTime()
{
	m_tvNextTime.setNow();
	//当前时间加上间隔时间
	m_tvNextTime += m_iTimeInterval;
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
	return 0;
}

ListTimer::ListTimer() : Timer()
{
	m_pNodeList = new DoubleList();
	pthread_mutex_init(&m_listLock, NULL);
	DoubleListInit(m_pNodeList);
}

ListTimer::~ListTimer()
{
}

void ListTimer::InsertIntoSortedList(ListTimerNode* pNewNode)
{
	pNewNode->updateNextTime();
	DoubleList* pInsertPoint = m_pNodeList; //默认插入点是头
	
	pthread_mutex_lock(&m_listLock);	
	//遍历链表，找到插入点（遍历到的节点比插入节点大）
	for_each_entry_at_list(entry, m_pNodeList)
	{
		ListTimerNode* pNode = CONTAINER_PTR(entry, ListTimerNode, list);
		if ((*pNode) >= (*pNewNode)) //有更晚的
		{
			pInsertPoint = entry;
			break;
		}
	}
	DoubleListInsertBefore(pInsertPoint, &pNewNode->list);
	pthread_mutex_unlock(&m_listLock);	
}
int ListTimer::AddTimer(int iMicroSecond, TIMER_HANDLER fnHandler, bool bRepeat)
{
	int iTimerId = NewTimerId();	
	ListTimerNode* pNewNode = new ListTimerNode(iTimerId, CALLBACK_TYPE_FUNC, iMicroSecond, (void*)fnHandler, bRepeat);
	InsertIntoSortedList(pNewNode);
	return iTimerId;
}

int ListTimer::AddTimer(int iMicroSecond, ITimerHandler* pHandler, bool bRepeat)
{
	int iTimerId = NewTimerId();	
	ListTimerNode* pNewNode = new ListTimerNode(iTimerId, CALLBACK_TYPE_CLASS, iMicroSecond, (void*)pHandler, bRepeat);
	InsertIntoSortedList(pNewNode);
	return iTimerId;
}

void ListTimer::RemovieTimer(int iTimerId)
{

}
int ListTimer::OnTimeout()
{
	pthread_mutex_lock(&m_listLock);
	//遍历链表，找到插入点（遍历到的节点比插入节点大）
	TimeVal tvNow;
	tvNow.setNow();
	int ret = MIN_SLEEP_MSEC;
	for (DoubleList* entry = m_pNodeList->next; entry != m_pNodeList; )
	{
		ListTimerNode* pNode = CONTAINER_PTR(entry, ListTimerNode, list);
		if (pNode->m_tvNextTime > tvNow)	
		{
			ret = (pNode->m_tvNextTime - tvNow);
			break;
		}
		printf("%d\n", 0);
		//执行函数
		if ( pNode->m_iCallType == CALLBACK_TYPE_FUNC)
		{
			(pNode->m_fnHandler)(pNode->m_iTimerId);
		}
		else
		{
			pNode->m_pHandler->Process(pNode->m_iTimerId);
		}

		//删除当前节点
		DoubleListRemove(entry);
		//下一个节点
		entry = entry->next;

		//如果有需要重新加入
		if (pNode->m_bRepeat)
		{
			InsertIntoSortedList(pNode);
		}
	}
	pthread_mutex_unlock(&m_listLock);
	//没有任何任务，休眠最小粒度
	return ret;		
}
