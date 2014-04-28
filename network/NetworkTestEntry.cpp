#include <assert.h>
#include <string.h>
#include <map>
#include <stdlib.h>
#include <unistd.h>

#include "Reactor.h"
#include "SelectReactorImpl.h"
#include "Address.h"
#include "Socket.h"
#include "client.h"
#include "utility/Tools.h"

using std::map;

typedef SelectReactor DemoReactor;

//阻塞非阻塞
//处理方式： TLV， \n方式 制定操作符做结束
class ClientHandler : public EventHandlerEmptyProxy
{
public:
	ClientHandler(int fd, DemoReactor* reactor) : socket_(fd)
	{
		reactor_ = reactor;
	} 
	virtual void handle_input(int fd);
	virtual	void handle_output(int fd);
	virtual void handle_close(int fd);
	virtual void handle_error(int fd){};
	virtual int get_fd() {return -1;}
private:
	char recv_buf_[1024];
	char send_buf_[1024];
	int send_size_;
	DemoReactor* reactor_;
	Socket  socket_;
};

void ClientHandler::handle_input(int fd)
{
	reactor_->remove_handler(fd, READ_EVENT);

	//传入一个缓冲区，读取一行
	int size = socket_.recv_line(recv_buf_, sizeof(recv_buf_));
	if (size <= 0) //对端关闭或者出现错误
	{
		handle_close(fd);
		//通知管理器，删除自己
		delete this;	
		return;
	}

	zues::Sleep(10);
	send_size_ = snprintf(send_buf_, sizeof(send_buf_),"#%s\n", recv_buf_);

	//对于对端关闭套接字，发生的可读事件
	printf("handle input, fd:%d, recv: %s\n", fd, recv_buf_);
	reactor_->register_handler(fd, this, WRITE_EVENT);
}

void ClientHandler::handle_output(int fd)
{
	reactor_->remove_handler(fd, WRITE_EVENT);
	if (socket_.send(send_buf_, send_size_))
	{
		handle_close(fd);
		//通知管理器，删除自己
		delete this;	
		return;
	}

	printf("handle output, fd:%d, send: %s\n", fd, send_buf_);
	reactor_->register_handler(fd, this, READ_EVENT);
}

void ClientHandler::handle_close(int fd)
{
	::close(fd);
	printf("handle close, fd:%d\n", fd);
	reactor_->remove_handler(fd, READ_EVENT | WRITE_EVENT | CLOSE_EVENT);
}

class Acceptor : public EventHandlerEmptyProxy
{
public:
	Acceptor(DemoReactor* reactor);
	virtual ~Acceptor()	;
	int open(INETAddress& addr);
	virtual void handle_input(int fd);
	virtual int get_fd() {return listen_sock_.get_fd();}
private:
	Socket listen_sock_;
	DemoReactor* reactor_;
};

Acceptor::Acceptor(DemoReactor* reactor)
{
	reactor_ = reactor;
}

Acceptor::~Acceptor()
{
}

int Acceptor::open(INETAddress& addr)
{
	return listen_sock_.listen(addr, MAX_BACKLOG_NUM);
}

void Acceptor::handle_input(int fd)
{
	INETAddress clientaddr;
	int client_fd = listen_sock_.accept(clientaddr);
	if (client_fd < 0)
	{
		return;
	}

	printf("acceptor: new client[%d], info[%s:%d]\n", client_fd, clientaddr.ip(), clientaddr.port());
	
	//注册读事件
	reactor_->register_handler(client_fd, new ClientHandler(client_fd, reactor_), READ_EVENT | CLOSE_EVENT);
}

int NetworkTestEntry(int argc, char* argv[])
{
	DemoReactor* r = new DemoReactor();
	INETAddress listen_addr("127.0.0.1", 12345);

	if (!strcmp(argv[1], "server"))
	{

		Acceptor* acceptor = new Acceptor(r);
		acceptor->open(listen_addr);

		r->register_handler(acceptor, READ_EVENT);
		for (;;)
		{
			r->handle_events(NULL);
		}
	}
	else
	{

		int count = 0;
		while (count++ < atoi(argv[1]))
		{
			Client* c = new Client(listen_addr);
			c->Start();
		}
		for (;;)
		{
			zues::Sleep(1000);
		}
	}
}

