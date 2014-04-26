#ifndef ZUES_CORE_MUTEX_H
#define ZUES_CORE_MUTEX_H

//互斥锁
class ThreadMutex
{
public:
	ThreadMutex();
	virtual ~ThreadMutex();

	//获取
	void acquire();
	//释放
	void release();
};

//互斥锁辅助
class ThreadMutexLocker
{
public:
	ThreadMutexLocker(ThreadMutex& mutex);
	~ThreadMutexLocker();
private:
	ThreadMutex& m_mutex;
};
#endif//ZUES_CORE_MUTEX_H

