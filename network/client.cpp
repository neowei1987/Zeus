#include <stdio.h>
#include "client.h"
#include "Socket.h"
#include "utility/Pressure.h"

int Client::Run()
{
	//创建一个客户端套接字
	Socket s;
	int ret = s.connect(server_addr_, 10);	
	if (ret < 0)
	{
		return -1;
	}

	int index = 0;
	char buf[1024];
	char recv_buf[1024];
	while (true)
	{
		int len = snprintf(buf, sizeof(buf), "%016d\n", index++);
		BEGIN_COST_CALCULATE("client");
		s.send(buf, len);
		s.recv_line(recv_buf, sizeof(recv_buf));
		END_COST_CALCULATE();
	}
}
