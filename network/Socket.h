#ifndef ZUES_NETWORK_SOCKET_H
#define ZUES_NETWORK_SOCKET_H

#include "Address.h"

/*
class Socket
{
public:
	//当有新的可用数据时调用
	int OnDataReadable(const char* buf, size_t len);	
	//当所有数据发送成功时调用
	int OnDataSendOK(const char* buf, size_t len);	
	//同步发送数据
	int SendData(const char* buf, size_t len, callback);
	//同步接受数据
	int RecvData(char* buf, size_t len);
	int OnDataWritable(const char* buf, size_t len);	
	int OnConnected(const char* buf, size_t len);	
	int OnClosed(const char* buf, size_t len);	

	//连接
	int connect(INETAddress& serveraddr, );	
private:

//是否阻塞
//同步异步
};

*/

enum SocketType
{	
	INVALID_TYPE = -1, //非法类型
	LISTEN_TYPE,		//监听类型 bind & listen
	ACTIVE_TYPE,		//主动连接类型 connect
	PASSIVE_TYPE,		//被动连接类型 accept
};

class Socket
{
public:
	//套接字
	Socket(int fd);
	Socket();

	int get_type() {return socket_type_;}
	int get_fd(){return fd_;}
	int listen(INETAddress& listen_addr, int backlog);
	int accept(INETAddress& peer_addr);
	int connect(INETAddress& server_addr, int timeout);
	int send(const char* buf, size_t len);
	int recv_line(char* buf, size_t len);
	int close();
private:
	void reset();
private:
	int socket_type_;	
	int fd_;
};

#endif//ZUES_NETWORK_SOCKET_H
