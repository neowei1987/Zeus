#ifndef ZUES_THREAD_H_
#define ZUES_THREAD_H_

#include <pthread.h>

class Thread 
{
public:
	Thread();
	virtual ~Thread();
	//启动
	int Start();
	//等待线程结束
	int Join();
	//暂停运行
	int Suspend();
	//恢复运行
	int Resume();
	//强制杀死进程
	int Kill();
	//由子类继承实现线程动作
	virtual int Run() = 0;

	//全局初始化
	static int GlobalInit();
private:
	static void* ThreadFunc(void* arg);
	static void ResumeHandler(int signo);
	static void SuspendHandler(int signo);
	static void TLSDestructor(void* ptr){}
private:
	static pthread_key_t m_stThreadKey;
	pthread_t m_tThread;

};

#endif //ZUES_THREAD_H_
