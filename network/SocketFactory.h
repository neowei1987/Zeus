
class SocketFactory
{
	//创建tcp套接字
	Socket* CreateTcpSocket();	
	//创建udp套接字
	Socket* CreateUdpSocket();	
	//创建unix套接字
	Socket* CreateUnixSocket();	

};
