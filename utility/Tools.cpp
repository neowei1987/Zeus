#include <sys/select.h>
#include <sys/time.h>
#include "Tools.h"
namespace zues
{

void Sleep(int iMicroSeconds)
{
	struct timeval delay;
	delay.tv_sec = iMicroSeconds / 1000;
	delay.tv_usec = (iMicroSeconds % 1000) * 1000;
	select(0, NULL, NULL, NULL, &delay);
}

TimeVal& TimeVal::setNow()
{
	gettimeofday(&m_tv, NULL);
	return *this;
}

TimeVal& TimeVal::operator += (long iMicroSecond)
{
	//printf("%d:%d\n", m_tv.tv_sec, m_tv.tv_usec);
	suseconds_t tmp = (m_tv.tv_usec + iMicroSecond * 1000);
	m_tv.tv_sec += (tmp / 1000000);		
	m_tv.tv_usec = tmp % 1000000;		
	//printf("%lld, %lld\n%d:%d\n", iMicroSecond, tmp, m_tv.tv_sec, m_tv.tv_usec);
	return *this;
}

const char* TimeVal::string()
{
	snprintf(m_strbuf, sizeof(m_strbuf), "%d:%d", m_tv.tv_sec, m_tv.tv_usec);
	return m_strbuf;
}

bool TimeVal::operator > (TimeVal& other)
{
	if (m_tv.tv_sec != other.m_tv.tv_sec)
	{
		return m_tv.tv_sec > other.m_tv.tv_sec;
	}
	else
	{
		return m_tv.tv_usec > other.m_tv.tv_usec;
	}
}

bool TimeVal::operator >= (TimeVal& other)
{
	if (m_tv.tv_sec != other.m_tv.tv_sec)
	{
		return m_tv.tv_sec > other.m_tv.tv_sec;
	}
	else
	{
		return m_tv.tv_usec >= other.m_tv.tv_usec;
	}
}

long TimeVal::operator - (TimeVal& other)
{
	long ret = (m_tv.tv_sec - other.m_tv.tv_sec) * 1000 + (m_tv.tv_usec - other.m_tv.tv_usec) / 1000;
	//printf("%d:%d - %d:%d = %lld\n", m_tv.tv_sec, m_tv.tv_usec, other.m_tv.tv_sec, other.m_tv.tv_usec, ret);
	return ret;
}

}
