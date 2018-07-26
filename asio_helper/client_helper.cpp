#include "client_helper.h"

// ����ֻ��ʹ�� asio ��ʹ��tcp�������ݷ��� gochart������ʽʵ�֡�

std::shared_ptr<AsioClient> InitAsioClient(const char* ip, const char* port)
{
	static boost::asio::io_context io_context;
	tcp::resolver resolver(io_context);
	auto endpoints = resolver.resolve(ip, port);
	std::thread t([]() { io_context.run(); });
	return std::make_shared<AsioClient>(io_context, endpoints);
}