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
#include "thread.h"

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
