#include <sys/select.h>
#include "Tools.h"
namespace zues
{

void Sleep(int iMicroSeconds)
{
	struct timeval delay;
	delay.tv_sec = iMicroSeconds / 1000;
	delay.tv_usec = (iMicroSeconds % 1000) * 1000000;
	select(0, NULL, NULL, NULL, &delay);
}

}
