#ifndef ZUES_NETWORK_ADDRESS_H
#define ZUES_NETWORK_ADDRESS_H

/*
struct sockaddr;
struct sockaddr_in; 
struct sockaddr_in6;
struct sockaddr_un;
struct sockaddr_dl;

socklen_t len = 0;
struct sockaddr_in addr;
bzero(&addr, sizeof(addr));
addr.sin_family= AF_INET;
addr.sin_len = sizeof(addr); 
addr.sin_port= htons(80);
//out of date
addr.sin_addr = inet_addr("19.2.12.12"); //INADDR_NONE 255.255.255.255的特殊性
inet_aton("192.158.1.1", &(addr.sin_addr));
const char* ip = inet_ntoa(addr.sin_addr); //不可重入，静态内存
//new 
#include <arpa/inet.h>
inet_pton(AF_INET, "192.158.12.1", &(addr.sin_addr));
char str[INET_ADDRSTRLEN];
const char* ip = inet_ntop(AF_INET, &(addr.sin_addr), str, sizeof(str));
*/

#include <arpa/inet.h>
#include <strings.h>
#include <netinet/in.h>

class INETAddress 
{
public:
	INETAddress()
	{
		sockaddr_len_ = sizeof(sockaddr_);
	}
	INETAddress(const char* ip, uint16_t port)
	{

		//转化为Ip4地址
		sockaddr_len_ = sizeof(sockaddr_in);
		sockaddr_in* addr_in = (sockaddr_in*)&sockaddr_;

		bzero(addr_in, sockaddr_len_);
		addr_in->sin_family = AF_INET;
		addr_in->sin_port = htons(port);
		inet_pton(AF_INET, ip, &(addr_in->sin_addr));
	}

	const char* ip()
	{
		const char* ip = inet_ntop(AF_INET, &(sockaddr_in_.sin_addr), strbuf_, sizeof(strbuf_));
		return ip;
	}
	uint16_t port()
	{
		return ntohs(sockaddr_in_.sin_port);
	}

	sockaddr* addr() 
	{
		return &sockaddr_;
	}
	socklen_t& size() 
	{
		return sockaddr_len_; 
	}
private:
	union
	{
		sockaddr sockaddr_;
		sockaddr_in sockaddr_in_;
	};
   	socklen_t sockaddr_len_;
	char strbuf_[64];

};
#endif//ZUES_NETWORK_ADDRESS_H
