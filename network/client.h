#ifndef _CLINET_H_
#define _CLINET_H_

#include "core/thread.h"
#include "network/Address.h"

class Client : public Thread
{
public:
	Client(INETAddress& server_addr) : server_addr_(server_addr) {}
	virtual int Run();
private:
	int send_request();
	int recv_response(); 
private:
	INETAddress server_addr_;	
};

#endif//_CLINET_H_

