#include <stdio.h>
#include <error.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <fstream>
#include <memory.h>
#include "core/thread.h"
#include "utility/Pressure.h"
#include "base/ZuesDefines.h"
#include "algorithm/Sort.h"
#include "memory/MemoryTestEntry.h"

using namespace std;

int BinaryTreeTestEntry(int argc, char* argv[]);
int PatternsTestEntry(int argc, char* argv[]);
int TimerTestEntry(int argc, char* argv[]);
int ListTestEntry(int argc, char* argv[]);
int NetworkTestEntry(int argc, char* argv[]);
int SegmentTreeTestEntry(int argc, char* argv[]);

inline void memset_tester(void* arg)
{
	static int data[1024];
	memset(data, 0, sizeof(data));
}

#define LISTEN_BACKLOG 50
#define MAX_EVENT_NUM 100

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

	class PrintThread :public Thread
{
public:
	int Run()
	{
		while (true)
		{
			fprintf(stderr, ".");
			sleep(1);
		}
		return 0;
	}	
};

void set_block_flag(int fd, bool non_block)
{
		
}

void default_handler(int signo)
{
	printf("signal eccors, sig: %d\n", signo);
}
int main(int argc, char* argv[])
{
	return SegmentTreeTestEntry(argc, argv);
	return NetworkTestEntry(argc, argv);
	return TimerTestEntry(argc, argv);
	return PatternsTestEntry(argc, argv);
	return ListTestEntry(argc, argv);
	return MemoryTestEntry(argc, argv);

	printf("%d\n", IS_POW_2(0));
	printf("%d\n", IS_POW_2(1));
	printf("%d\n", IS_POW_2(2));
	printf("%d\n", IS_POW_2(17));


	printf("%d\n", POW(4, 3));
	printf("%d\n", POW(2, 10));
	printf("%d\n", POW(5, 1));
	printf("%d\n", POW(5, 0));

	printf("%d\n", UP_TO_POW_2(3));
	printf("%d\n", UP_TO_POW_2(4));
	printf("%d\n", UP_TO_POW_2(16));
	printf("%d\n", UP_TO_POW_2(17));

	//sleep不占用cpu时间
	BEGIN_COST_CALCULATE("sleep");
	//sleep(3);
	END_COST_CALCULATE();

	/*延迟测试用*/
	int num = 0;
	int* data = NULL;
	BEGIN_COST_CALCULATE("user calclute");
	num = 100 * 1024;
	data = new int[num];
	END_COST_CALCULATE();

	BEGIN_COST_CALCULATE("bubble sort");
	int i = 0;
	while (i < num)
	{
		data[i] = rand();
		i++;
		//fprintf(stderr, "%d\n", data[i]);
	}
	//BubbleSort(data, num);
	ofstream fs("./bubble.txt");
	i = 0;
	while (i < num)
	{
		fs << data[i] << endl;
		i++;
	}
	END_COST_CALCULATE();


	BEGIN_COST_CALCULATE("quick sort");
	int i = 0;
	while (i < num)
	{
		data[i] = rand();
		i++;
		//fprintf(stderr, "%d\n", data[i]);
	}
	QuickSort(data, num);
	ofstream fs("./quick.txt");
	i = 0;
	while (i < num)
	{
		fs << data[i] << endl;
		i++;
	}

	END_COST_CALCULATE();

	BEGIN_TIMES_CALCULATE("memset", 10, memset_tester, NULL);
	END_TIMES_CALCULATE();
	return 0;

	//一个函数可以执行多少次??

	BinaryTreeTestEntry(argc, argv);
	
	return 0;

	Thread* thread = new PrintThread();
	thread->Start();

	while (true)
	{
		char c = getchar();
		switch (c)
		{
			case 's':
				thread->Suspend();
				break;
			case 'r':
				thread->Resume();
				break;
			case 'k':
				thread->Kill();
				break;
		}
	}
	int epoll_fd = epoll_create(10);
	if (epoll_fd == -1)
	{
		fprintf(stderr, "error create epoll, errno: %d\n", errno);
		exit(-1);	
	}

	int listen_fd = socket(AF_INET, SOCK_STREAM, 0);	
	if (listen_fd < 0)
	{
		fprintf(stderr, "error create socket, errno: %d\n", errno);
		exit(-1);	
	}

	unsigned short port = 13400;
	struct sockaddr_in my_addr;
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(port); 
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int ret = bind(listen_fd, (struct sockaddr*)&my_addr, sizeof(my_addr));
	if (ret < 0)
	{
		handle_error("error bind port");
	}

	ret = listen(listen_fd, 50);
	if (ret < 0)
	{
		handle_error("error listen");
	}

	signal(SIGUSR1, default_handler);

	struct epoll_event ev, events[MAX_EVENT_NUM];
	ev.data.fd = listen_fd;
	ev.events = EPOLLIN | EPOLLET;

	epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &ev);
	while (true)
	{
		printf("epoll wait begin!\n");
		int nfds = epoll_wait(epoll_fd, events, MAX_EVENT_NUM, 10000);
		if (nfds < 0)
		{
			if (errno == EINTR)	
			{
				printf("epoll wait back, timeout or signal!\n");
				continue;
			}
			handle_error("error epoll_wait");
		}
		else if (nfds == 0)
		{
			printf("epoll wait back, timeout!\n");
			continue;
		}

		for (int i = 0; i < nfds; ++i)
		{
			if (events[i].data.fd == listen_fd)
			{
				struct sockaddr_in cli_addr;
				socklen_t alen = sizeof(struct sockaddr);
				int cli_fd = 0;
				//高并发（一次触发， 多个客户端连接）
				while ((cli_fd = accept(listen_fd, (struct sockaddr*)&cli_addr, &alen)) == 0)
				{
					printf("new client coming, ip:%s, port:%d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));	
					//非阻塞模式？
					ev.data.fd = cli_fd;
					ev.events = EPOLLIN | EPOLLET;
					epoll_ctl(epoll_fd, EPOLL_CTL_ADD, cli_fd, &ev);
				}

				if (cli_fd < 0 && errno != EAGAIN)
				{
					handle_error("error accept");					
				}
			}
			else
			{
			}
		}
	}
}
