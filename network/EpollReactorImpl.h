#ifndef ZUES_NETWORK_EPOLL_RECTOR_IMPL_H
#define ZUES_NETWORK_EPOLL_RECTOR_IMPL_H

#include <sys/epoll.h>
#include "Reactor.h"

class EpollReactorImpl: public ReactorImpl
{
public:
	EpollReactorImpl();
	~EpollReactorImpl();

	virtual void register_handler(EventHandler* handler, EventType event);
	virtual void register_handler(int fd, EventHandler* handler, EventType event);
	virtual void remove_handler(EventHandler* handler, EventType event);
	virtual void remove_handler(int fd, EventType event);
	virtual void handle_events(TimeVal* timeout);

private:
	int epoll_fd_;
};

typedef Reactor<EpollReactorImpl> EpollReactor;

#endif//ZUES_NETWORK_EPOLL_RECTOR_IMPL_H
