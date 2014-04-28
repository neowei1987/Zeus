
class ServerBase
{
public:
	int Run();	

protected:
	//接收到数据
	int OnRecvData(const char* buf, size_t len);
	//新的客户端接入
	int OnNewClient();
};
