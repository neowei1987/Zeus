#include <unistd.h>
#include "base/ZuesDefines.h"
#include "EpollReactorImpl.h"


struct EpollHandler 
{
	EventHandler* handler_;
	int fd_;
};

EpollReactorImpl::EpollReactorImpl()
{
	epoll_fd_ = epoll_create(0);
}

EpollReactorImpl::~EpollReactorImpl()
{
	::close(epoll_fd_);
}

void EpollReactorImpl::register_handler(EventHandler* handler, EventType event)
{
	EpollHandler* epoll_handler = new EpollHandler();
	epoll_handler->handler_ = handler;
	epoll_handler->fd_ = handler->get_fd();
	
	int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
}

void EpollReactorImpl::register_handler(int fd, EventHandler* handler, EventType event)
{
}

void EpollReactorImpl::remove_handler(EventHandler* handler, EventType event)
{
	int fd = handler->get_fd();
}

void EpollReactorImpl::remove_handler(int fd, EventType event)
{
}

void EpollReactorImpl::handle_events(TimeVal* timeout)
{
}


