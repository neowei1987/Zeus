
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
	
private:
		
};


