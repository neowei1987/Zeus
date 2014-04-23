#include "Pressure.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>

CostCalculater::CostCalculater(const char* desc) : m_pDesc(desc)
{
	m_tck = sysconf (_SC_CLK_TCK);
	m_time_head = times( &m_time_buf_head );
}

CostCalculater::~CostCalculater()
{
	m_time_end = times( &m_time_buf_end );
	printf ("++++++++++++++++%s+++++++++++++\n", m_pDesc);
	printf ("start_time is : %f\n", m_time_head/ (double)m_tck);
	printf ("end_time is : %f\n", m_time_end / (double)m_tck);

	printf ("user time is : %f\n", ((m_time_buf_end.tms_utime - m_time_buf_head.tms_utime) / (double)m_tck));   /*用户进程所耗费的时间*/
	printf ("systime time is : %f\n", ((m_time_buf_end.tms_stime - m_time_buf_head.tms_stime) / (double)m_tck));
	printf ("child user time is : %f\n", ((m_time_buf_end.tms_cutime - m_time_buf_head.tms_cutime) / (double)m_tck));
	printf ("child sys time is : %f\n", ((m_time_buf_end.tms_cstime - m_time_buf_head.tms_cstime) / (double)m_tck));
	printf ("++++++++++++++++++++++++++++++\n");
}

bool TimesCalculater::m_sbExit = false;
TimesCalculater::TimesCalculater(int iRunSeconds, TIMES_CALCULATER_FUNC fnTest, void* arg)
{
	m_iTimes = 0;
	m_fnTest = fnTest;
	m_pArg = arg;
	m_iRunSeconds = iRunSeconds;
	m_sbExit = false;
}

TimesCalculater::~TimesCalculater()
{
	printf("RunSeconds: %d, Times: %d\n", m_iRunSeconds, m_iTimes);	
}

void TimesCalculater::SignalAlarmHandler(int signo)	
{
	m_sbExit = true;
}

int TimesCalculater::Run()
{
	m_iTimes = 0;
	//安装ALARM信号
	sig_t ret = signal(SIGALRM, TimesCalculater::SignalAlarmHandler);
	int res = alarm(m_iRunSeconds);
	printf("alarm ret: %d\n", res);
	while (!m_sbExit)
	{
		m_fnTest(m_pArg);
		m_iTimes++;
	}
	signal(SIGALRM, ret);
	return 0;
}
