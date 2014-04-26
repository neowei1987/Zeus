#ifndef ZUES_NETWORK_ADDRESS_H
#define ZUES_NETWORK_ADDRESS_H

class INETAddress
{
public:
	INETAddress(uint32_t ip, uint16_t port);
	uint16_t getPort() const;
	uint32_t getIP()const ;
	sockaddr* addr() const;
	size_t size() const;
};
#endif//ZUES_NETWORK_ADDRESS_H
