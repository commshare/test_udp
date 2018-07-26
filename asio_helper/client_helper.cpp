#include "client_helper.h"

// ����ֻ��ʹ�� asio ��ʹ��tcp�������ݷ��� gochart������ʽʵ�֡�

std::shared_ptr<AsioClient> InitAsioClient(const char* ip, const char* port)
{
	static boost::asio::io_context io_context;
	static tcp::resolver resolver(io_context);
	static auto endpoints = resolver.resolve(ip, port);
	auto client = std::make_shared<AsioClient>(io_context, endpoints);
	std::thread t([]() { io_context.run(); });
	return client;
}