#ifndef ZUES_NETWORK_REACTOR_H
#define ZUES_NETWORK_REACTOR_H

#include "base/ZuesDefines.h"

typedef uint32_t EventType;

enum 
{
	READ_EVENT = 1,
	ACCEPT_EVENT = 1,
	WRITE_EVENT = 2,
	TIMEOUT_EVENT = 4,
	SIGNAL_EVENT = 8,
	CLOSE_EVENT = 16,
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
	virtual int get_fd() = 0;
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
