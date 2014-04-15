#include "thread.h"
#include <signal.h> 

#define SIGRESUME SIGUSR2
#define SIGSUSPEND SIGUSR1

pthread_key_t Thread::m_stThreadKey;

//线程局部存储，编译器支持
//考虑使用线程局部存储，但是涉及信号处理，有可能信号不安全
__thread int g_suspend = 0; 

int Thread::GlobalInit()
{
	int ret = 0;

	struct sigaction suspendAction;
	struct sigaction resumeAction;

	sigemptyset(&suspendAction.sa_mask);
	suspendAction.sa_handler =  SuspendHandler;  
	suspendAction.sa_flags = 0;
	sigaddset(&suspendAction.sa_mask, SIGRESUME);  
	sigaction( SIGSUSPEND, &suspendAction, NULL);  

	sigemptyset(&resumeAction.sa_mask);
	resumeAction.sa_handler = ResumeHandler;  
	resumeAction.sa_flags = 0;
	sigaddset(&resumeAction.sa_mask, SIGSUSPEND);  
	sigaction( SIGRESUME, &resumeAction, NULL);

	//ret = pthread_key_create(&m_stThreadKey, Thread::TLSDestructor);

	return ret;
}

Thread::Thread()
{

}

Thread::~Thread()
{

}

//启动
int Thread::Start()
{
	int ret = pthread_create(&m_tThread, NULL, Thread::ThreadFunc, (void*)this);	   
	return ret;
}

int Thread::Suspend()
{
	return pthread_kill(m_tThread, SIGSUSPEND);
}

int Thread::Resume()
{
	return pthread_kill(m_tThread, SIGRESUME);
}

//等待线程结束
int Thread::Join()
{
	return -1;
}

//杀死进程
int Thread::Kill()
{
	return -1;
}

void* Thread::ThreadFunc(void* arg)
{
	//int suspend = 0;
	//pthread_setspecific(m_stThreadKey, &suspend); 
	Thread* pThis = (Thread*)arg;
	while (true)
	{
		pThis->Run();	
	}
	return NULL;
}

void Thread::ResumeHandler(int signo)
{
	//void* ptr = pthread_getspecific(m_stThreadKey);  该函数有可能信号不安全
	//int& suspend = *((int*)ptr);
	g_suspend = 0; 
}

void Thread::SuspendHandler(int signo)
{
	g_suspend = 1;  

	sigset_t nset;  
	pthread_sigmask(0, NULL, &nset);  
	/* make sure that the resume is not blocked*/  
	sigdelset(&nset, SIGRESUME);  
	while(g_suspend) sigsuspend(&nset);  

	//void* ptr = pthread_getspecific(m_stThreadKey); 
	//int& suspend = *((int*)ptr);
}

