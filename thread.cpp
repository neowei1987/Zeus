#include "thread.h"
#include <signal.h> 

#define SIGSUSPEND SIGUSR1
#define SIGRESUME SIGUSR2
pthread_key_t Thread::m_stThreadKey;

//线程局部存储，编译器支持
//考虑使用线程局部存储，但是涉及信号处理，有可能信号不安全
__thread int g_suspend = 0; 

/*
const char http_is_crlf[256] = {
	['\r'] = 1, ['\n'] = 1,
};
*/

int Thread::GlobalInit()
{
	int ret = 0;

	struct sigaction suspendAction;
	struct sigaction resumeAction;
	struct sigaction killAction;

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

	/*
	通过发送信号，在信号处理函数里面调用pthread_exit(BE_KILLED)来强制杀死线程
	sigemptyset(&killAction.sa_mask);
	killAction.sa_handler = KillHandler;  
	killAction.sa_flags = 0;
	//sigaddset(&killAction.sa_mask, SIGSUSPEND);  
	sigaction( SIG_KILL_THREAD, &killAction, NULL);
	*/

	//确保能够做线程取消
	//pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	//收到取消命令，立刻取消线程
	//thread_setcanceltype(PTHREAD_CANCEL_ASYCHRONOUS, NULL);

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
	int ret = pthread_join(m_tThread, NULL);
	return ret;
}

//杀死进程
int Thread::Kill()
{
	return pthread_cancel(m_tThread);
}

void* Thread::ThreadFunc(void* arg)
{
	//int suspend = 0;
	//pthread_setspecific(m_stThreadKey, &suspend); 
	Thread* pThis = (Thread*)arg;
	int ret = 0;
	while (true)
	{
		ret = pThis->Run();	
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

