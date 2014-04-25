#ifndef ZUES_UTILITY_TOOLS_H
#define ZUES_UTILITY_TOOLS_H

#include "base/ZuesDefines.h"

NAMESPACE_BEGIN(zues)

const int MIN_SLEEP_MSEC = 10;

class TimeVal
{
public:
	TimeVal& setNow();
	TimeVal& operator += (long iMicroSecond);
	bool operator > (TimeVal& other);
	bool operator >= (TimeVal& other);
	long operator - (TimeVal& other);
private:
	struct timeval m_tv;
};

//精确sleep, 精度为10ms，如果小于10ms，则精度大大降低
void Sleep(int iMicroSeconds);

NAMESPACE_END()

#endif//ZUES_UTILITY_TOOLS_H
