#ifndef ZUES_NETWORK_SELECT_RECTOR_IMPL_H
#define ZUES_NETWORK_SELECT_RECTOR_IMPL_H

#include <sys/select.h>
#include "Reactor.h"

class DemuxTable;

class SelectReactorImpl : public ReactorImpl
{
public:
	SelectReactorImpl();
	~SelectReactorImpl();

	virtual void register_handler(EventHandler* handler, EventType event);
	virtual void register_handler(int fd, EventHandler* handler, EventType event);
	virtual void remove_handler(EventHandler* handler, EventType event);
	virtual void remove_handler(int fd, EventType event);
	virtual void handle_events(TimeVal* timeout);

private:
	DemuxTable* demux_table_; //多路复用表
	fd_set* readfds_;
	fd_set* writefds_;
	fd_set* exceptfds_;
};

typedef Reactor<SelectReactorImpl> SelectReactor;
#endif//ZUES_NETWORK_SELECT_RECTOR_IMPL_H
