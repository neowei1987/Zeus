#ifndef ZUES_UTILITY_PRESSURE_H
#define ZUES_UTILITY_PRESSURE_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/times.h>

#include "core/thread.h"
/*
 * 压力测试，要测的内容包括：
 * 1， 服务器的性能 用户数，用户请求方式，用户请求次数，查看服务器压力，服务器响应时间，QPS
 * 2， 算法性能: 数据量，计算耗时
 * 3， 接口调用次数，例如，1秒中可以调用多少次memset
 * */

#define BEGIN_COST_CALCULATE(desc) \
{\
	CostCalculater _calculater(desc);

#define END_COST_CALCULATE \
}

#define BEGIN_TIMES_CALCULATE(desc, seconds, fnTest, arg) \
{\
	TimesCalculater _calculater(seconds, fnTest, arg);\
	_calculater.Start();

#define END_TIMES_CALCULATE() \
	_calculater.Join();\
}

//计算一段函数的耗时
class CostCalculater
{
public:
	CostCalculater(const char* desc);
	~CostCalculater();
private:
	const char* m_pDesc;
	struct tms m_time_buf_head;
	struct tms m_time_buf_end;
	long  m_tck;
	clock_t m_time_head;
	clock_t m_time_end;
};

typedef void (*TIMES_CALCULATER_FUNC)(void*);

//计算一段代码可执行多少次
class TimesCalculater : public Thread
{
public:
	TimesCalculater(int iRunSeconds, TIMES_CALCULATER_FUNC fnTest, void* arg);
	~TimesCalculater();

	int Run();
private:
	static void SignalAlarmHandler(int signo);	
private:
	TIMES_CALCULATER_FUNC m_fnTest;	
	void* m_pArg;
	int m_iTimes;
	int m_iRunSeconds;
	static bool m_sbExit;
};

//测试一个函数可以执行多少次
//创建一个线程，循环执行加一，同时开一个定时器
//

#endif//ZUES_UTILITY_PRESSURE_H
