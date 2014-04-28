#ifndef ZUES_NETWORK_REACTOR_H
#define ZUES_NETWORK_REACTOR_H

#include "base/ZuesDefines.h"

typedef uint32_t EventType;

enum 
{
	READ_EVENT = 1,		//可读
	ACCEPT_EVENT = 1,	//可读 listen
	WRITE_EVENT = 2,	//可写
	KEEALIVE_TIMEOUT_EVENT = 4,	//保活超时
	READ_TIMEOUT_EVENT = 4,	//读超时
	WRITE_TIMEOUT_EVENT = 4,	//写入超时
	CLOSE_EVENT = 16,	//对端关闭，正常关闭，异常关闭（进程被kill掉）
	CONNECT_OK_EVENT = 32,	//连接成功 非阻塞connect
	CONNECT_FAIL_EVENT = 64,	//连接失败，非阻塞connct
};

class TimeVal;

//一个EventHandler可以对应多个fd， 但是一个fd只能对应一个Handler
//一个Handler关心fd的多个事件
class EventHandler 
{
public:
	virtual void handle_input(int fd) = 0;
	virtual void handle_output(int fd) = 0;
	virtual void handle_timeout(int fd) = 0;
	virtual void handle_close(int fd) = 0;
	virtual void handle_error(int fd) = 0;
	virtual int get_fd() = 0;
};

//EventHandle空代理，实现空操作函数
class EventHandlerEmptyProxy : public EventHandler
{
public:
	virtual void handle_input(int fd){};
	virtual void handle_output(int fd){};
	virtual void handle_timeout(int fd){};
	virtual void handle_close(int fd){};
	virtual void handle_error(int fd){};
};

template <class REACTOR_IMPL>
class Reactor 
{
public:
	Reactor()
	{
		reactor_impl_ = new REACTOR_IMPL;
	}
	void register_handler(EventHandler* handler, EventType event)
	{
		reactor_impl_->register_handler(handler, event);
	}
	void register_handler(int fd, EventHandler* handler, EventType event)
	{
		reactor_impl_->register_handler(fd, handler, event);
	}
	void remove_handler(EventHandler* handler, EventType event)
	{
		reactor_impl_->remove_handler(handler, event);
	}
	void remove_handler(int fd, EventType event)
	{
		reactor_impl_->remove_handler(fd, event);
	}
	void handle_events(TimeVal* timeout)
	{
		reactor_impl_->handle_events(timeout);
	}
private:
	REACTOR_IMPL* reactor_impl_;
};

class ReactorImpl 
{
public:
	virtual void register_handler(EventHandler* handler, EventType event) = 0;
	virtual void register_handler(int fd, EventHandler* handler, EventType event) = 0;
	virtual void remove_handler(EventHandler* handler, EventType event) = 0;
	virtual void remove_handler(int fd, EventType event) = 0;
	virtual void handle_events(TimeVal* timeout) = 0;
};

#endif//ZUES_NETWORK_REACTOR_H
