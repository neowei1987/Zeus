#include "sys/select.h"

#include "base/ZuesDefines.h"
#include "SelectReactorImpl.h"

class DemuxTable 
{
public:
	DemuxTable();
	void set(int fd, EventHandler* handler, EventType event);
	bool get(int fd, EventHandler*& handler, EventType& event);
	int convert(fd_set* readfds, fd_set* writefds, fd_set* exceptfds);
	struct Tuple
	{
		EventHandler* handler_;
		EventType event_;
	};
	Tuple table_[FD_SETSIZE];  //select 最大可处理数量
};

DemuxTable::DemuxTable()
{
	int i = 0;
	int count = COUNT_OF(table_);
	while (i++ < count)
	{
		table_[i].handler_ = NULL;
	}
}

void DemuxTable::set(int fd, EventHandler* handler, EventType event)
{
	if (table_[fd].handler_)
	{
		table_[fd].handler_ = handler;
	}
	table_[fd].event_ = event;
}

bool DemuxTable::get(int fd, EventHandler*& handler, EventType& event)
{
	bool ret = false;
	if (table_[fd].handler_)
	{
		handler = table_[fd].handler_;
		event = table_[fd].event_;
		ret = true;
	}
	return ret;
}

int DemuxTable::convert(fd_set* readfds, fd_set* writefds, fd_set* exceptfds)
{
	return 0;
}

SelectReactorImpl::SelectReactorImpl()
{
	demux_table_ = new DemuxTable();
}

SelectReactorImpl::~SelectReactorImpl()
{
	if (demux_table_)
	{
		delete demux_table_;
	}
}

void SelectReactorImpl::register_handler(EventHandler* handler, EventType event)
{
	int fd = handler->get_fd();
	demux_table_->set(fd, handler, event);
}

void SelectReactorImpl::register_handler(int fd, EventHandler* handler, EventType event)
{
	demux_table_->set(fd, handler, event);
}

void SelectReactorImpl::remove_handler(EventHandler* handler, EventType event)
{
	int fd = handler->get_fd();
	demux_table_->set(fd, handler, event);
}

void SelectReactorImpl::remove_handler(int fd, EventType event)
{
}

void SelectReactorImpl::handle_events(TimeVal* timeout)
{
	int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);	   
}


