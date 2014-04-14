#include <netinet/in.h>

#if 0
struct sockaddr;
struct sockaddr_in; 
struct sockaddr_in6;
struct sockaddr_un;
struct sockaddr_dl;

socklen_t len = 0;
struct sockaddr_in addr;
bzero(&addr, sizeof(addr));
addr.sin_family= AF_INET;
addr.sin_len = sizeof(addr); 
addr.sin_port= htons(80);
//out of date
addr.sin_addr = inet_addr("19.2.12.12"); //INADDR_NONE 255.255.255.255的特殊性
inet_aton("192.158.1.1", &(addr.sin_addr));
const char* ip = inet_ntoa(addr.sin_addr); //不可重入，静态内存
//new 
#include <arpa/inet.h>
inet_pton(AF_INET, "192.158.12.1", &(addr.sin_addr));
char str[INET_ADDRSTRLEN];
const char* ip = inet_ntop(AF_INET, &(addr.sin_addr), str, sizeof(str));

//试着发送已经排队待发的任何数据，然后正常终止
close();

struct sockaddr_in localaddr;
socklen_t locallen = sizeof(localaddr);
struct sockaddr_in peeraddr;
socklen_t peerlen = sizeof(peeraddr);

getsockname(fd, &localaddr, &locallen);
getpeername(fd, &peeraddr, &peeraddr);

//exec()如何获取connfd   
//（1）将connfd格式化为字符串，参数传递
//（2）将某个描述字总是设置成已连接套接字

//主动关闭的一方，进入time_wait状态

void sig_func(int signo)
{
	return;//显式的return是为了警告该return语句可能中断了某个系统调用
}

struct sigaction act;
act.sa_handler = sig_func;// 信号处理函数
sigemptyset(&act.sa_mask); //信号掩码，任何阻塞的信息都不能递交给进程。信号处理程序运行时被捕获的信号是阻塞的
act.sa_flag = 0; //除了SIGALRM, 其他信息都设置SA_RESTART,来保证信号中断的系统调用被内核自动重启
sigaction(signo, &act, &oldact);
//缺省时，信号是不排队的

//进程终止处理：子进程结束时会给父进程SIGCHILD，缺省忽略。如果父进程不处理，则子进程成为僵尸进程
//正确处理SIGCHLD，wait waitpid

//慢系统调用 EINTR的处理
// accept, read, write, select, open都可以考虑自己重启,但有一个例外connect，如果connect被信号中断
// 而且不自动重启，则必须调用 select 来等待连接完成


//正确处理ECHLD，避免留下僵尸进程
while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
{

}

//accept返回前，连接夭折【服务器在调用accept前sleep一段时间，客户端发送RST】
//
//服务进程崩溃【kill掉服务子进程】
//服务段主动关闭连接，发送FIN包，能够收到客户端的ack，进入FIN_WAIT2状态；客户端此刻进入CLOSE_WAIT状态
//客户端此时正阻塞于fget，然后我们输入一行，客户端向服务器发送数据(不会报错)，然后读取响应【此时接收到服务器的fin包】
//客户端收到FIN包不符合预期，close，发送FIN包给服务器，此时服务器接收到FIN包，进入TIME_WAIT状态
//客户端进入LAST_ACK状态，当收到服务器的fin_ack后，进入CLOSED状态
//
//以上客户端阻塞于terminal,socket,通过poll、select来解决此问题

//服务器发送了FIN包，但是客户端依旧写入，第一次写入将引发一个RST【发送本身是成功的】；但是第二次写入，将引发SIGPIPE
//系统对SIGPIPE的处理是终止进程

//写一个已经接收了FIN包的套接字是可行的，但是写一个接受了RST的套接字是错误的
//
//服务器主机崩溃,客户端ETIMEOUT
//如何发现：主动给服务器发送数据，超时时间设短一点【默认9分钟，重传12次】
//如何发现：SO_KEEPALIVE选项

//服务器主机崩溃后重启
//建立连接；重启服务器，客户端发送数据【成功】，接收数据【RST】返回ECONNRESET

//服务器关机，跟服务进程崩溃类似
//
//
fd = fileno(fp);

int pselect(int maxfdp1, fd_set* readset, fd_set* writeset, fd_set* exceptset, const struct timespec* timeout, const sygset_t* sigmask);
阻塞指定的信号
调用pselect来临时重置信号集合

int poll(struct pollfd* fdarray, unsigned long nfds, int timeout);
对方发送FIN包，也被认为是普通数据,POLLIN
监听套接字上新连接的可用性， POLLIN
连接存在错误，POLLIN POLLERR read都会返回-1

int getsockopt(int fd, int level, int optname, void* optval, socklen_t* optlen);
int setsockopt(int fd, int level, int optname, const void* optval, socklen_t* optlen);
常用：
SO_ERROR
SO_LINGER
	shutdown(SHUT_RD); //套接字不能再发出接收请求，进程仍可发送数据。接受缓冲区被清空，再接收的数据被TCP抛弃
						//如果套接字正recv阻塞了，会发生神马？ TODO
	shutdown(SHUT_WR); //优雅关闭， 套接字不能再发出发送请求，进程仍可接受数据。TCP将发送缓冲区中的数据一直发送， 然后发送FIN包
	close lonoff = 0;  //立即返回，接收缓冲区被清空，发送缓冲区的数据一直发送，然后FIN
	close lonoff = 1 linger = 0;  //立即返回，发送RST给对方，进入CLOSED状态，发送、接收缓冲区被清空
	close lonoff = 1, linger != 0;  //在linger时间内尝试发送所有数据，以及fin; 如果停滞时间内，套接字未进入CLOSED，则返回EWOULDBLOCK,发送数据丢失
									//closd的成功返回，表示TCP已经确认了数据，但是应用程序不一定读到数据。
									//让客户知道服务器已经读到数据的一个方法：调用shutdown(SHUT_WR),并等待对方close本地连接[read返回0]
									//另外一个方法：application ack
SO_SNDBUF
SO_RCVBUF
	在connect、listen之前调用,一般缓冲区大小要超过带宽延迟积[带宽 * RTT]，否则便没法充分利用管道。如果超过TCP max窗口65535字节，则启用长胖管道选项
SO_SNDLOWAT
	tcp默认2028
SO_RCVLOWAT
	tcp，udp默认1
SO_SNDTIMEO
SO_RcVTIMEO
SO_KEEPALIVE
SO_REUSEADDR
	(1)子进程仍然存在
	1,启动一个listen服务器
	2,连接请求到达，派生一个子进程为之服务
	3，监听服务器终止，但子进程仍在服务中
	4，重新启动listen服务器（一般失败，除非使用SO_REUSEADDR）
	(2) 同一端口，多个ip实例
SO_NODELAY
	禁止Nagle算法[默认情况下, 如果可能，TCP总是发送最大分组大小的分组；对于小分组，延迟发送来防止任何时刻连接上有多个待确认的小分组]	
	telnet小分组特别明显，如果WLAN延迟特别严重
	延迟ACK，等待一段时间才发出ack，期望期间有数据发回给对方
	有些时候，不产生ack可以捎带的反向通信量，这样子客户会有明显延时，此时就可以调用SO_NODELAY
	多个小分界发送单个逻辑请求，不适合使用Nagle，延迟ack。但是可以如下三个方法来修复：
	（1）writev 推荐
	(2)copy到一个缓冲区
	（3）so_nodelay，2 * write 不推荐


int flag = fcntl(fd, F_GETFL, 0);
flag |= O_NONBLOCK; //设置为非阻塞
flag &= ~O_NONBLOCK;// 设置为阻塞
fcntl(fd, F_SETFL, flag);

UDP recvfrom有可能永远阻塞（udp不可靠丢失了，请求丢失或者应答丢失），简单的设置超时，区分不出是哪种丢失??
异步错误，只有udp调用connect之后才能接受到此类错误。 send但是失败了
使用udp connect，getsockname可以进行外出接口的确定【connect时内核进行本地ip地址选择，通过目的ip进行路由表搜索，本地操作】

connect 一个非法地址不会返回错误，而send时会出错

守护进程
fork 
	die
setsid
signal(SIGHUP, SIG_IGN);
fork
	die
chdir("/");
umask(0);
for (i = 0; i < MAXFD, ++i)
{
	close(i);
}
openlog();

套接字超时
(1) SIGALRM 
(2) select + read/write
(3) send/recv SO_RCVTIMEO SO_SNDTIMEO

size_t readv(int fd, const struct iovec* iov, int iovcnt)
size_t writev();

sendmsg
recvmsg
发送文件描述符，授权信息

排队数据量
非阻塞， MSG_PEEK | MSG_NOWAIT

描述字 vs 标准IO
fileno fdopen
全双工 【r+】
write + fflush/fseek/fsetpos/rewind + read 但是对于套接字，调用lseek会失败
better way: 在一个套接字上，打开两个标准IO流，一个读取，一个写入
标准IO 行缓冲，全缓冲，不缓冲

socketpair 传递描述字（父子关系）
unix socket 非亲缘关系

非阻塞的connect返回EINPROGRESS, 而不是EWOULDBLOCK

非阻塞是缓冲区管理变复杂了 环形buffer

while (true)
{
	解阻塞;
	if (global_var) //信号处理函数里面设置，来进一步减小时间窗口,但仍有竞争
	{
		return;
	}
	sigprocmask(SIG_UNBLOCK, &sigset_alarm, NULL);	
	recvfrom()
	阻塞;
	sigprocmask(SIG_BLOCK, &sigset_alarm, NULL);	
}
以上程序尽可能把时间窗口缩小了，但是依然有竞争

while (true)
{
	阻塞alarm;
	sigprocmask(SIG_BLOCK, &sigset_alarm, NULL);	
	pselect(..., sigset_empty); //pselct阻塞期间，有可能被中断，因为没有阻塞alaram
	recvfrom()
}

以上程序利用了pselect的操作原子性来避开竞争

sigsetjmp
siglongjmp(sigjmp_buf jmpbuf, );


更优雅的办法 select + pipe(IPC) 当信号发生时，往通道中写入一个字节；将触发select可读，超时

udp的超时重传
计算RTT，计算RTO, 然后+指数回退

重传二义性：
（1） 请求丢了（2）确认丢了 （3）RTO太小

除了序列号+时间戳（对方确认的时候再传回来） =》 解决重传二义性

UDP并发服务
（1）简单服务器，读取请求，回复请求。
（2）与客户端交换多个数据包（bind一个临时端口到与客户端通信的套接字，要告诉客户端这个临时端口，并要求其配合）

select 一直指示一个异常条件，知道进程读越过带外数据

信号驱动IO
SIGIO信号建立信号处理程序 
	signal(SIGIO, sigio)
设置套接字属主 fcntl(F_SETOWN)
	ioctl(sockfd, F_SETDOWN, getpid());
激活套接字的信号驱动IO　fcntl(F_SETFL, O_ASYNC)
	ioctl(sockfd, FIOASYNC);

监听套接字上使用SIGIO， 只有一种情况：新连接完成
UDP 信号IO：
每次信号发生时，recvfrom。但是信号不排队~ 将套接字改为非阻塞，信号发生时，一直读到EWOULDBLOCK。读到的数据写入循环队列
主循环
block(SIGIO); // 阻塞IO信号
for (;;)
{
	while (nqueue == 0)	//信号阻塞了，可以放心的读取
	{
		sigsuspend(&zeromask); //睡眠期间不阻塞任何信号，当有信号发生时，立刻返回；并设置原来的mask
	}
	解阻塞SIGIO
		process...
	阻塞SIGIO
	nqueue--; //信号阻塞了，可以放心的写
}

线程
共享：大多数数据 指令 打开的文件 信号处理函数 当前工作目录 用户id，组id
独立： 栈、信号掩码、errno 线程id 优先级 线程id, TLS

int pthread_create(pthread_t* tid, const pthread_attr_t* attr, void* (*func)(void* ), void* arg);
int pthread_join(pthread_t tid, void** status); //status为线程执行函数的返回值
pthread_t pthread_self();
int pthread_detach(phtread_t tid); //脱离之后， 线程结束的状态将无从得知， 类似于守护进程，所有的资源将立刻被释放
void pthread_exit(void* status);

malloc free不可重入的，这两个函数操纵相同的静态变量
线程安全

pthread_once_t rl_once = PTHREAD_ONCE_INIT;
pthread_once(&rl_once);

pthread_key_t rl_key;
pthread_key_create(&rl_key, void (*destructor)(void*)); //释放内存

ptr = pthread_get_specific(rl_key); //没有设置过，则返回NULL
pthread_set_specific(rl_key, ptr);

pthread_mutex_t mutex = PTHREAD_MUTEXT_INIT; //静态变量初始化
pthread_mutex_init(&mutex); //
pthread_mutex_lock(&mutex);
pthread_mutex_unlock(&mutex);
互斥锁加锁开销并不大~ 10%

轮询
pthread_cond_wait(pthread_cond_t* cptr, pthread_mutex_t* mptr); //解锁互斥锁， wait条件变量（休眠），在别的线程发出信号之后，
//锁住互斥锁
pthread_cond_signal(pthread_cond_t* cptr);
phtread_cond_broadcast(pthread_cond_t* cptr);//广播，唤醒所有线程
pthread_cond_timedwait(pthread_cond_t* cptr, pthread_mutex_t* mptr, const struct timespec* abstime); //要醒来的绝对时间
//使用绝对时间的好处： 如果函数提前返回（很可能捕获了一个信号），可以不更改参数；但必须调用gettimeofday
//

icmpd
socket(AF_INET, SOCKET_RAW, SOCKTYPE_ICMP);  //当udp send失败时，通过这个可以把这个错误，发送给客户端
客户端 udp send。并通过unix域套接字，将套接字传给icmpd，icmpd通过getsockname获取绑定的其他信息，供系统
发送icmp错误时， 对比参照返回.

#endif
