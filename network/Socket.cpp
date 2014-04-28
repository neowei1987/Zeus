#include <unistd.h>
#include <sys/socket.h>
#include "Socket.h"
#include "base/ZuesDefines.h"

Socket::Socket(int fd)
{
	fd_	 = fd;
	socket_type_ = PASSIVE_TYPE;
}

Socket::Socket()
{
	socket_type_ = INVALID_TYPE;
	fd_ = -1;
}

void Socket::reset()
{
	close();
}

int Socket::close()
{
	::close(fd_);
	fd_ = -1;
	socket_type_ = INVALID_TYPE;
	return 0;
}

int Socket::listen(INETAddress& listen_addr, int backlog)
{
	reset();

	int fd = ::socket(AF_INET, SOCK_STREAM, 0);	
	if (fd < 0)
	{
		PRINT_ERROR("socket failed.");
		return -1;
	}
	int on = 1;
	int ret = ::setsockopt( fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );
	if (ret < 0)
	{
		PRINT_ERROR("setsockopt failed.");
		return -1;
	}

	ret = ::bind(fd, listen_addr.addr(), listen_addr.size());
	if (ret < 0)
	{
		PRINT_ERROR("bind failed.");
		return -1;
	}

	ret = ::listen(fd, MAX_BACKLOG_NUM);
	if (ret < 0)
	{
		PRINT_ERROR("listen failed.");
		return -1;
	}

	fd_ = fd;
	socket_type_ = LISTEN_TYPE;
	return 0;
}

int Socket::accept(INETAddress& peer_addr)
{
	int client_fd = ::accept(fd_, peer_addr.addr(), &(peer_addr.size()));
	if (client_fd < 0)
	{
		PRINT_ERROR("accept failed");
		return -1;
	}
	return client_fd;
}

int Socket::connect(INETAddress& server_addr, int timeout)
{
	reset();
	int fd = socket(AF_INET, SOCK_STREAM, 0);	
	if (fd < 0)
	{
		PRINT_ERROR("socket failed.");
		return -1;
	}
	int ret = ::connect(fd, server_addr.addr(), server_addr.size());
	if (ret < 0)
	{
		PRINT_ERROR("connect failed.");
		return -1;
	}

	fd_ = fd;
	socket_type_ = ACTIVE_TYPE;
	return 0;
}

int Socket::send(const char* buf, size_t len)
{
	int left = len;
	int ret = 0;
	while (left > 0)
	{
		ret = ::send(fd_, buf - (len - left), left, 0);
		if (ret < 0)
		{
			PRINT_ERROR("send failed");
			return -1;
		}
		else
		{
			left -= ret;
		}
	}
	return 0;
}

int Socket::recv_line(char* buf, size_t len)
{
	int ret = 0;
	int recv = 0;
	char* start = buf;
	while (true)
	{
		ret = ::recv(fd_, buf, len, 0);
		if (ret > 0)
		{
			len -= ret;
			//遍历找到结束符号
			while ((ret-- >0) && (*buf++ != '\n'));

			if (ret >= 0) 
			{
				*buf = '\0';
				return buf - start;
			}
		}
		else if (ret == 0)
		{
			printf("peer close the socket\n");
			return 0;
		}
		else
		{
			PRINT_ERROR("recv failed");
			return -1;
		}
	}
	return 0;
}

