#include "core/thread.h"

class GlobalInitializer
{
public:
	GlobalInitializer()
	{
		Thread::GlobalInit();
	}

	~GlobalInitializer()
	{
	}
};


static GlobalInitializer g_initGlobal;

