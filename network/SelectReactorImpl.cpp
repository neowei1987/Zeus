#include "sys/select.h"

#include "base/ZuesDefines.h"
#include "SelectReactorImpl.h"

class DemuxTable 
{
public:
	DemuxTable();
	int unset(int fd);
	int unset(int fd, EventType event);
	int set(int fd, EventHandler* handler, EventType event);
	int get(int fd, EventHandler*& handler, EventType& event);
	int convert(int& minfd, int& maxfd, fd_set* readfds, fd_set* writefds, fd_set* exceptfds);
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
int DemuxTable::unset(int fd)
{
	table_[fd].handler_ = NULL;
}

int DemuxTable::unset(int fd, EventType event)
{
	table_[fd].event_ &= (~event);
	if (table_[fd].event_ == 0)
	{
		table_[fd].handler_ = NULL;
	}
}

int DemuxTable::set(int fd, EventHandler* handler, EventType event)
{
	table_[fd].handler_ = handler;
	table_[fd].event_ |= event;
	return 0;
}

int DemuxTable::get(int fd, EventHandler*& handler, EventType& event)
{
	bool ret = -1;
	if (table_[fd].handler_)
	{
		handler = table_[fd].handler_;
		event = table_[fd].event_;
		ret = 0;
	}
	return ret;
}

int DemuxTable::convert(int& minfd, int& maxfd, fd_set* readfds, fd_set* writefds, fd_set* exceptfds)
{
	FD_ZERO(readfds);
	FD_ZERO(writefds);
	FD_ZERO(exceptfds);

	int i = 0;
	int count = COUNT_OF(table_);
	maxfd = -1;
	minfd = -1;
	while (i++ < count)
	{
		if (table_[i].handler_)
		{
			if (minfd == -1) //记录最小fd
			{
				minfd = i;	
			}
			maxfd = i; //更新最大fd
			if (table_[i].event_ & READ_EVENT)
			{
				FD_SET(i, readfds);	
			}
			if (table_[i].event_ & WRITE_EVENT)
			{
				FD_SET(i, writefds);	
			}
			if (table_[i].event_ & CLOSE_EVENT)
			{
				FD_SET(i, exceptfds);	
			}
		}
	}

	return 0;
}

SelectReactorImpl::SelectReactorImpl()
{
	demux_table_ = new DemuxTable();
	readfds_ = new fd_set;
	writefds_ = new fd_set;
	exceptfds_ = new fd_set;
}

SelectReactorImpl::~SelectReactorImpl()
{
	DELETE(demux_table_);
	DELETE(readfds_);
	DELETE(writefds_);
	DELETE(exceptfds_);
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
	demux_table_->unset(fd, event);
}

void SelectReactorImpl::remove_handler(int fd, EventType event)
{
	demux_table_->unset(fd, event);
}

void SelectReactorImpl::handle_events(TimeVal* timeout)
{
	int ret = 0;
	int minfd = 0;
	int maxfd = 0;
	EventHandler* handler = NULL;
	EventType event;

	demux_table_->convert(minfd, maxfd, readfds_, writefds_, exceptfds_);
	//printf("min: %d, max: %d\n", minfd, maxfd);
	ret = select(maxfd + 1, readfds_, writefds_, exceptfds_, NULL);	   
	if (ret > 0) //event
	{
		for (int fd = minfd; fd <= maxfd; ++fd) //遍历查找
		{
			if (demux_table_->get(fd, handler, event)) //被移除
			{
				continue;
			}

			//printf("fd: %d, event: %d\n", fd, event);
			if ((event & READ_EVENT) && FD_ISSET(fd, readfds_))
			{
				//printf("fd: %d, read event\n", fd);
				handler->handle_input(fd);
			}
			if ((event & WRITE_EVENT) && FD_ISSET(fd, writefds_))
			{
				//printf("fd: %d, write event\n", fd);
				handler->handle_output(fd);
			}
			if ((event & CLOSE_EVENT) && FD_ISSET(fd, exceptfds_))
			{
				printf("fd: %d, except event\n", fd);
				handler->handle_close(fd);
			}
		}
	}
	else if (ret == 0) //timeout
	{
	}
	else //error
	{
	}
}


