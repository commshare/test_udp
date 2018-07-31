#include <thread>
#include "client_helper.h"

bool ConnectRakNetServer(const char*sip, int sport, int updateInterval, const std::shared_ptr<AsioClient>& asioClient);

int main()
{
	const int updateInterval = 25;		// ���¼��
	const char* server = "127.0.0.1";	// ���Է�������ַ
	int raknetPort = 5001;				// raknet server �˿ں�

	boost::asio::io_context io_context;
	std::shared_ptr<AsioClient> asioClient = InitAsioClient(io_context, "127.0.0.1", "3333");
	std::thread thrd1(ConnectRakNetServer, server, raknetPort, updateInterval, asioClient);
	io_context.run();
}