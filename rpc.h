rpc:

消息传递
	管道
		具有父子关系的进程间使用
		随进程持续的，最后一个进程关闭该对象为止
		单路数据流
		int pipe(int fd[2])
		如果全双工，则需要搞两个管道
	FIFO
		有名管道，解决了上面的亲缘关系问题
		随文件系统持续的，unlink之后从文件系统中删除
		int mfifo(const char* pathname, mode_t mode);

	消息队列 System_V
		随内核持续的，内核重新自检，重启之后
	消息队列 Posix
		随文件系统持续的，一直存在到显示删除
同步
	mutex
		随进程持续的，最后一个进程关闭该对象为止
   	condition
		随进程持续的，最后一个进程关闭该对象为止
   	rwlock
		随进程持续的，最后一个进程关闭该对象为止
   	file_lock
		随进程持续的，最后一个进程关闭该对象为止
   	semphore System_V
		随内核持续的，内核重新自检，重启之后
共享内存
	匿名、有名
		随内核持续的，内核重新自检，重启之后
远程过程调用

管道 & FIFO

FILE* popen(const char* command, const char* type = "r|w");
nt pclose(FILE* stream);

写入管道或者FIFIO的原子性：
如果写入长度 <= PIPE_BUF 则原子性；如果剩余缓冲区不足，则直接返回EAGAIN
如果写入长度 > PIPE_BUF 则原子性；如果剩余缓冲区不少于一个字节，则写入成功，返回写入字节数。如果已满，则直接返回EAGAIN

写入一个没有打开为读的PIPE，内核产生一个SIGPIPE。如果处理了这个信号，则write返回EPIPE 

单个服务器，多个客户端
服务器，打开一个管道，用于读取客户请求；
技巧：服务器同时打开一个管道（写入方式），用于防止read返回0【当管道对端没有任何写入方时返回】

open（O_RDONLY）将阻塞到第一个客户只写打开FIFO为止；

字节流，消息
（1）带内特殊终止序列
（2）显示长度
（3）每次连接一个记录

打开管道时，必须小心，因为有许多规则制约着open的阻塞与否
迭代服务器 【DDOS】 并发服务器

Posix 消息队列
内核持续性，消息， 消息链表
mq_unlink删除队列文件；但是mq_close减少引用技术，直到0才真正无效

mq_notify(mqd_t mqdes, const struct sigevent * notification);
当有消息放入队列时，触发信号，或者创建一个线程执行一个指定的函数

信号处理函数：禁止调用mq_notify, mq_receive, printf等信号不安全的函数。如果想利用这种方法来异步通知，考虑使用全局标志
volatile sig_automic_t mqflag = 0; 当信号发生时，置1；由其他线程来安全的读取。
for(;;)
{
	//阻塞SIGUSR1
	while (mqflag == 0)
	{
		sigsuspend(zeroset);
	}
	mqflag = 0; //重置标记位
	mq_notify(); //重新注册
	mq_receive();
	sigunblock(); //解阻塞
}
依旧有问题， 当队列从没有数据变为有数据时，信号才会发生。
解决方法：非阻塞，读到没有数据为止

除了上面方法（信号处理函数仅仅置了一个标志位），还有效率更高的方法：sigwait
for (;;)
{
	sigwait(&newmask, &signo); //阻塞newmask的信号，并等待这些信号中有一个或多个待处理，这时返回其中一个信号
	if (signo == SIGUSR1)
	{
		//处理
	}
}

select + pipe write + signal 
信号处理函数：
	往pipe写入一个字节 // write信号安全
for ()
{
	FD_SET(fd[0], &rset);
	select(); //选择管道的读端，读到一个字节，表示新号发生了
	if (FD_ISSET())
	{
		//重新注册
		//循环读取
	}
}

触发线程
	在线程函数里面，直接调用mq_notify, mq_receive即可，线程安全

共享内存 + 互斥锁 + 信号量 =》 消息队列 
（1）链表
（2）共享内存, open时候的竞争
（3）mq_notify  => sigqueue();  实时信号

SystemV 消息队列
消息复用，类型字段 & 优先级字段 
一个服务器 + 多个客户端
（1）同一个队列 （type = 1: 客户端进程发给服务器；type=pid: 服务器发给客户端进程 ）
(2) 1 + n消息队列 (1： 服务器众所周知， n: 每个客户(每台机器)单独创建一个队列)

systemV消息队列上使用select poll等
（1）服务器创建一个管道，fork子进程，由子进程阻塞在msgrecv调用中 。当一个消息准备好之后，子进程读出来，然后写进管道。
	触发select返回，父进程read管道读到消息内容。
弊端：上面的方法，一条消息被处理了三次。 
解决方法：父进程创建一个共享内存，然后把管道用作父子进程之间的一种标志。
为啥Posix不需要这么复杂？ 因为它提供了一个mq_notify

同步
pthread_mutex_trylock EBUSY

协作性锁？？
如果共享数据是一个链表，那么操作该链表的所有线程都必须要在实际操纵之前获取该互斥锁。不过也没有办法防止某个线程不
获取互斥锁，就操纵该链表

编程技巧：努力把共享数据 + 同步变量收集到一个结构中
生产者，消费者模式：
（1）所有的生产者完成之后，才启动消费者。
(2) N个生产者 + 1个消费者 【生成者一单生成完成，让睡眠的线程即可醒来】 《==== 条件变量

上锁冲突~ 

进程终止时自动使用所持有的锁：fcntl记录锁

读写锁
多个读者 + 1个写者
利用互斥锁 + 条件变量 实现读写锁
线程可能阻塞于pthread_cond_wait时调用期被取消，通过线程取消清理程序来纠正此问题
pthread_cleanup_push(void (*cleanup_func)(void* arg), (void*)arg);
pthread_cleanup_pop(int execute);


文件读写锁 fcntl
fcntl(int fd, F_SETLK|F_SETLKW|F_GETLK, struct flock* lock);
lock.l_type = F_UNLCK|F_WRLCK|F_RDLCK;
lock.l_whence = SEEK_CUR|SEEK_SET|SEEK_END;
lock.l_start = 0;
lock.l_len = 0;
劝告性上锁
强制性上锁【增加标志位，而无须额外的系统调用】
如果有多个进程在更新一个文件，那么所有进程必须使用某种上锁形式协作。否则，一个进城违规就可以引发大混乱。
如果进程崩溃了，内核会自动释放他的记录锁

文件作锁用【利用检测文件存在，创建该文件是原子的。】
open(O_CREAT|O_EXCL); 
(1) 进程崩溃，文件依然存在。写入pid，判断进程是否存在？ 进程id有可能重用。。。
（2）如果某进程一打开了锁文件，则另外的进程进行了polling；或者sleep
（3）open，unlink设计文件系统，耗时性能差。

最好使用fcntl

Posix信号灯
P操作, wait
	while (N <= 0)
		wait
	N--;
V, signal
	N++
	signal
二值信号灯,可以用于互斥；N=1初始化
	sem_wait();
	...
	sem_post(); //此操作可以由其他线程来执行，也可以解锁。此处不同于一般的互斥锁
信号量有一个与之关联的状态，它的计数，信号灯挂出操作总是被记住。然而当向一个条件变量发送信号时如果没有线程等待在
该条件变量上，则该信号丢失。
信号灯，原定位为进程同步；而互斥锁，条件变量定位为线程同步。

计数信号灯

有名信号灯，线程同步 & 进程同步
sem_open();
关闭一个信号灯，并不会将它从系统中删除，而应该通过sem_unlink

int sem_getvalue(sem_t* sem, int* valp); 返回信号灯的当前值

分析：
sem_post是信号处理函数中可安全调用的。
互斥锁，为互斥而优化的；
条件变量，为等待而优化的；
信号灯，既可以等待，又可以互斥，因而导致更高的开销和更高的复杂性

单个生成者 + 单个消费者 + 环形缓冲区


内存信号灯
int sem_init(sem_t* sem, int shared, unsigned int value);
shared = 0, 进程持续性
shared = 1， 共享内存 

多个生产者 + 单个消费者
每个生产者：
while (true)
{
	sem_wait(&sem_empty);	 //等待缓冲区有剩余空间
	sem_wait(&sem_mutex);
	if (没有新的资源可以放入了)
	{
		sem_post(&sem_empty); //上面占用了一个空位，如果没有资源放入，需要释放
		sem_post(&sem_mutex);
		return;
	}
	//放入新的资源
	sem_post(&sem_mutex);
	//将数据放入缓冲区	
	sem_post(&sem_stored); // 放入了新的数据
}
单个消费者：

while (true)
{
sem_wait(&sem_stored); //等待新资源
sem_wait(&sem_mutex);
//取出资源
sem_post(&sem_mutex);
sem_post(&sem_empty); //释放新空间
}

多个生产者 + 多个消费者
每个生产者：
while (true)
{
	sem_wait(&sem_empty);	 //等待缓冲区有剩余空间
	sem_wait(&sem_mutex);
	if (没有新的资源可以放入了)
	{
		sem_post(&sem_stored); //对于每个生产者，生产了一个资源空的资源给消费者。
		sem_post(&sem_empty); //上面占用了一个空位，如果没有资源放入，需要释放
		sem_post(&sem_mutex);
		return;
	}
	//放入新的资源
	sem_post(&sem_mutex);
	//将数据放入缓冲区	
	sem_post(&sem_stored); // 放入了新的数据
}
每个消费者：
while (true)
{
sem_wait(&sem_stored); //等待新资源
sem_wait(&sem_mutex);
if (判断是否已经完成任务)
{
	sem_post(&sem_stored); //
	sem_post(&sem_mutex);
	//消费者终止
	return;
｝
//取出资源
sem_post(&sem_mutex);
sem_post(&sem_empty); //释放新空间
}

单个生产者 + 单个消费者 + 多个缓冲区【特例：双缓冲区】
生产者：
while (true)
{
	sem_wait(&sem_empty);	 //等待缓冲区有剩余空间
	sem_wait(&sem_mutex);
	//临界区
	sem_post(&sem_mutex);
	//将数据放入缓冲区	
	sem_post(&sem_stored); // 放入了新的数据

}
消费者：
while (true)
{
	sem_wait(&sem_stored); // 等待放入新的数据
	sem_wait(&sem_mutex);
	//临界区
	sem_post(&sem_mutex);
	//将数据取出缓冲区
	sem_post(&sem_empty); //有了新的剩余空间
}
如何实现有名信号灯：
（1）创建文件【O_CREAT|O_EXCL】
（2）写入内容
		a, 如果是用FIFO来实现，则写入两个fd, 一个用于读FIFO，一个用于写FIFO；信号数量、等待等通过文件内容来表示
		b, 如果是用共享内存，则写入互斥锁，信号量、信号数量等

System_V  信号灯
创建一个信号灯，创建 + 初始化，不是原子。竞争~ 

共享内存

mmap();
flags: PROT_READ | PROT_WRITE | PROT_EXEC | MAP_SHARED | MAP_PRIVATE | MAP_FIXED
privat: 修改只对该进程可见，而不改变底层支撑对象。

父子共享内存， mmap的时候指定MAP_SHARED然后再fork
作用：
	内存操作代替读写文件
	为没有亲缘关系的进程间提供共享的内存区

匿名内存映射
	不必创建一个文件，写入内容，然后。。。mmap
	MAP_ANON【匿名】时，fd 可以传入-1，忽略offset
	open("/dev/zero")初始化0 

如果文件大小跟映射大小一样（不是页大小的倍数）则：
访问内存大小 + 省下的不到一页，不会出问题【这一部分不会写入到文件中】；再向后访问会段错误
如果文件大小小于映射大小，则：
访问内存大小 + 省下的不到一页【不会出问题，但这一部分不会写入到文件】；超过的页面【SIGBUS】, 没有映射【SIGSEG】
处理一个持续增长的文件：

指定一个大于该文件大小的内存映射大小，跟踪跟文件的大小，然后。。。
munmap(); //如果private的，则修改丢失


msync(void* addr, int len, int flags = MS_ASYNC(异步写) | MS_SYNC(同步写) | MS_INVALIDATE(使高速缓存的数据失效));


POSIX共享内存区
int fd = shm_open(const char* filename, int oflag, mode_t mode); // 打开新建一个共享内存区对象
	然后这个fd依旧需要mmap
int shm_unlink(const char* filename);

ftrancate(int fd, off_t length);//修改文件大小

SystemV共享内存区
int shm_get(key_t key, size_t size, int oflag); //创建共享内存
void* shmat(int shmid, const void* shmaddr, int flag); //将共享内存链接到调用进程的地址空间
int shmdt(const char* shmaddr);
int shmctl(int shmid, int cmd, struct shmid_ds* buff);

门
IPC
RPC(同一个机器) RPC(不同主机)

int door_create();
int fattach(int fd, const char* );
int door_call();

