#if 0
//网络模型
//并发服务器
//	1, fork子进程
//	2, select
//	3, 创建子线程
//
//	4, 进程池
//	5, 线程池
//		新的问题：数量多了咋办？ 数量少了咋办？ 线程之间如何同步数据？

服务器描述				CPU时间 (秒，与基准之差)
迭代服务器					0

客户端设计方法：
1 停等模式，批处理时效率极低。当他等待在用户输入而阻塞时，无法监视网络事件（譬如对方关闭连接）
2 select同时监听用户输入与网络事件，但是不能正确处理批处理。shutdown来解决，当客户端请求完毕时，shutdown发送fin包
3 非阻塞IO [最快，但开发比较复杂]
4 fork子进程，父子进程中一个处理从服务器到客户的数据，一个处理从客户到服务器的数据
5 使用双线程，而不是双进程 [性价比最高]

服务器设计方法：
############ TCP迭代服务器
	当前客户被处理完之前，新到达的客户无法被服务

############ TCP并发服务器，每个客户一个子进程，由父进程来accept
	同一时间可以为多个客户服务
	唯一的限制: 操作系统对同一用户同时可拥有的进程数控制
	问题：fork子进程时所消耗的CPU时间
	分析：与其他几种并发服务器比较，他的cpu时间最大，这是由于对每个客户fork一个子进程造成的
	代码：
	for(;;)
	{
		connfd = accept(listenfd);	
		if (fork() == 0)
		{
			close(listenfd);
			do_something(connfd);
			close(connfd);
			exit(0);
		}
		close(listenfd);
	}

############ TCP预先派生子进程服务器，accept无上锁保护
	优点：不需要引入父进程fork的开销，新客户就能得到处理
	缺点：每次启动服务，父进程必须猜测到底需要派生多少子进程。如果不考虑派生子进程，一旦所有子进程都被客户请求所占有，
			那么此时到达的请求暂时被忽略，知道一个进程可用
	如何解决：由父进程来监视子进程数，如果低于某个阈值再派生额外的子进程。如果空闲子进程数高于某个阈值，则终止部分，
			因为过多的可用子进程也会降低性能(惊群问题)。
	代码：
	父进程：
	for (i = 0; i < nchild; i++)
	{
		fork();
	}
	子进程：
	{
		for(;;)
		{
####		select(listenfd);	
			connfd = accept(); // 当有一个客户连接到来时，N个睡眠进程均被唤醒，惊群问题。 最好不要有太多闲着没事干的进程
			do_something(connfd);
			close(connfd);
		}
	}
	连接在子进程中的分布：内核调度算法使得连接分布大致均匀
	别样选择：####，但是，如果有多个进程阻塞于同一个套接字，那么阻塞在诸如accept这样子的函数要比阻塞在select上好。
			但是，如果你要监听更多的套接字，就必须用select了。
	分析：####方法不如直接调用accept， 增加了系统调用，内核为处理冲突，而增加了开销			

############## TCP预先派生子进程服务器，accept使用文件锁保护
	有些系统的accept实现不支持所有子进程都阻塞在accept上，则可以考虑使用锁来保证只有一个子进程在accept上等待
	代码：
	子进程：
	{
		for(;;)
		{
			file_lock();
			connfd = accept(); 
			file_unlock();
			do_something(connfd);
			close(connfd);
		}
	}
	分析：加锁增加了服务器的进城控制CPU时间
	连接在子进程中的分布：均匀分布文件锁到等待进程

############## TCP预先派生子进程服务器，accept使用线程互斥锁保护
	有些系统的accept实现不支持所有子进程都阻塞在accept上，则可以考虑使用锁来保证只有一个子进程在accept上等待
	代码：
	子进程：
	{
		for(;;)
		{
			//进程互斥锁 互斥锁变量必须存储在共享内存中，必须通知线程函数库互斥锁是在不同进程间共享的
			mutext_lock();
			connfd = accept(); 
			mutex_unlock();
			do_something(connfd);
			close(connfd);
		}
	}
	分析：相比文件锁，线程互斥锁性能更好一些，避免了文件操作消耗

############## TCP预先派生子进程服务器，传递套接字
	由父进程调用accept，然后再将接受的已连接套接字传递给子进程。绕过上锁，但是父进程必须通过某种方式向子进程传递套接字。
	代码：
	父进程：
	for (i = 0; i < nchild; i++)
	{
		为每个子进程，创建一个与之通信的字节流套接口[pipe]
		fork() == 0
		{
			dup pipe读端到标准输出
			关闭pipe读端
			关闭pipe写端
			关闭listenfd
			//more
		}
		else
		{
			存储pipe写端，以及子进程pid
			关闭pipe读端
		}
	}
	for (;;)
	{
		//优化：如果没有可用子进程，可以通过把listenfd给clr掉来拒绝新的连接
		select(listenfd + every stream pipe fd);
		for (i = 0; i < nsel; ++i)
		{
			if (listenfd)
			{
				connfd = accept();
				接受连接，寻找合适的子进程，通过字节流套接口发送connfd
				//分析下，由于总是从第一个子进程开始搜索起，所以越考前，处理的连接越多。影响分布
			}
			for (int i = 0; i < nchild; ++i)
			{
				if (clientfd)
				{
					读取字节流套接口，如果读到了，说明，子进程空了。更改子进程状态
				}
			}

		}
	
	}

	子进程：
	{
		for(;;)
		{
			connfd = read_fd(); //读取新的套接字，也就是新的连接，即父进程新分配的任务
			do_something(connfd);//处理任务
			close(connfd);//关闭套接字
			write(stderr_fileno, "", 1); //告诉父进程，我处理完了
		}
	}

	分析：比较复杂，因为父进程必须跟踪子进程的忙闲状态，以便给空闲子进程传递新的套接字。 而之前的方法进程无须关心哪个子进程
			接受链接，而由操作系统处理这个系统。性能方面，比起其他三种更耗时一些。不推荐使用

############ TCP并发服务器，每个客户一个线程，由父进程来accept
	分析：快于任何预先分配子进程版本，说明线程的cpu代价比起进程小多了
	代码：
	for(;;)
	{
		connfd = accept(listenfd);	
		pthread_create(doit, connfd); //创建线程
	}

############## TCP预先创建线程服务器，各个线程各自accept，考虑使用mutex来加锁
	分析：该版本可能是最快的。并且使用mutex加锁比直接accept【引起惊群】更高效一些
	代码：
	子线程程：
	{
		for(;;)
		{
			mutext_lock();
			connfd = accept(); 
			mutex_unlock();
			do_something(connfd);
			close(connfd);
		}
	}

############## TCP预先创建服务器程序，主线程统一accept
	由父线程调用accept，然后再将接受的已连接套接字通过循环队列 + 互斥锁 + 信号量的方式通知给子线程
		该方法较上面的方法，稍微更慢一点。这边用了更多，例如信号量
	代码：
	父线程：
	for (;;)
	{
		connfd = accept();
		mutex_lock();
		将connfd放入循环队列
		cond_signal();
		mutex_unlock();
	}

	子线程：
	{
		for(;;)
		{
			mutex_lock();
			while (队列是空的)
			{
				cond_wait();
			}
			connfd = read_from_queue(); //读取新的套接字，也就是新的连接，即父进程新分配的任务
			do_something(connfd);//处理任务
			close(connfd);//关闭套接字
			mutex_unlock();
		}
	}


使用场景：当系统负载比较轻时，比较传统的并发服务器就够了。但是如果负载更高了，就考虑其他方法了
如果可以，让进程或者线程都掉用accept比起父进程、夫线程调用accept来的更简单、更高效。
select冲突问题，如果只需要选择一个套接字，accept更高效。
线程，比进程更高效

//客户端
FD_ZERO(&rset);
FD_SET(sockfd, &rset);
FD_CLR(sockfd, &rset);
for (;;)
{
	select(maxfd, &rset, &wset, &eset, NULL);
	if (FD_ISSET(sockfd, &rset))
	{
	}

}
//服务器
for (;;)
{
	nready = select();
	//监听套接字处理
	if (FD_ISSET(listenfd, &rset))
	{
		connfd = accept();
		FD_SET(connfd, &rset);


		//nready检测来加速
	}

	//遍历所有的client
	for ()
	{
		connfd = ...;
		if (FD_ISSET(connfd, &rset))
		{
			//nready检测来加速
		}
	}
}

for (;;)
{
	nready = poll(clients, num, INFTIM);

	if (clients[0].revents & POLLRDNORM) // 监听套接字可读
	{
		connfd = accept();

		//设置
		clients[i].fd == connfd;
		clients[i].events = POLLRDNORM;
	}

	//遍历其他clients
	 for ()
	 {
		 connfd = ...;
		if (clients[i].revents & (POLLRDNORM | POLLERR)) //数据可读 错误
		{
			n = read();
			//errno检测
			//n检测

		}

	 }
}
//单进程服务所有客户，遇到恶意客户，有可能拒绝服务，解决方案：
//1， 使用非阻塞型IO
//2， 让每个客户由单独的控制线程来提供服务
//3， 对IO操作设置超时

//5种IO模型
1, 阻塞性IO
2, 非阻塞IO
	polling 进程反复调用recv等待返回成功指示
3，IO复用
4，信号IO
5，异步IO

停等版本
批处理模式

select + 非阻塞IO
在增加代码复杂度的情况下，是否值得用非阻塞IO来编写程序呢？答案是否定的。每当我们需要使用非阻塞IO时，把
应用程序分成多个进程或者线程通常会更简单


fork() == 0
{
	while (read_from_socket())
	{
		write_to_stdout();
	}
	kill(getpid(), SIGTERM);
	exit(0);
}
else
{
	while (read_from_stdin)
	{
		write_to_socket();
	}
	shutdown(sockfd, SHUT_WR); //此处不可以close，套接字的引用计数 = 2 不会发送FIN包
	pause(); //正常情况下等待子进程来Term掉
}

非阻塞connect
(1)非阻塞标志
（2）select + timeout
(3) 直接返回0，连接成功（本地连接有可能）
（4）连接成功，可写[有可能连接成功，对方数据道到来，这种情况下可读可写]
（5）连接失败，可读可写
(6) 如何判断连接是否建立：
	getpeername() ENOTCONN？ getsockopt(SO_ERROR)得到套接字上待处理的错误
	read(buf, len = 0) 0？ read返回的errno指明了连接失败的原因
	connect再一次 EISCONN? 
复杂。。。

阻塞connect被中断返回EINTR的正确处理： 调用select

非阻塞accept

考虑select[客户端此时调用connect] + sleep【此时客户端更改Linger选项，发送RST】 + accept[此时服务器阻塞在此调用上，
直到另一个客户来连接] 模拟一个比较繁忙的服务器
理论上，select之后的accept不应该阻塞的
解决方案：
（1）非阻塞套接字
（2）在后面的accept调用中忽略以下错误：EWOULDBLOCk EPROTO ECONNABORT等【考虑多平台移植性】

for (;;)
{
	connfd = accept(); //接收用户连接
	pthread_create(..., doit, connfd); //创建新的线程，为之服务
}
void* doit(void* arg)
{
	//...
	close(connfd); // 线程共享，所以在此关闭，而不是让夫线程关闭
	return NULL;
}

#endif
