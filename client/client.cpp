#include <thread>
#include "client_helper.h"

bool ConnectRakNetServer(const char*sip, int sport, int updateInterval, const std::shared_ptr<AsioClient>& asioClient);

int main()
{
	const int updateInterval = 25;		// ���¼��
	const char* server = "127.0.0.1";	// ���Է�������ַ
	int raknetPort = 5001;				// raknet server �˿ں�

	std::shared_ptr<AsioClient> asioClient = InitAsioClient("127.0.0.1", "3333");
	std::thread thrd1(ConnectRakNetServer, server, raknetPort, updateInterval, asioClient);

	for (;;)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1000));
	}
}