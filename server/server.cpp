#include <thread>

#ifdef _MSC_VER
#pragma comment(lib, "ws2_32.lib")
#endif

bool StartRakNetServer(int port, int broadcastInterval, const char* broadcastMsg);

int main()
{
	const int dataSzie = 400;				// ���ݰ���С
	const int broadcastInterval = 100;		// �㲥���
	const int raknetPort = 5001;			// raknet server �˿ں�

	char msg[dataSzie] = { 0 };
	memset(msg, 97, dataSzie - 1);	// msg =  "aaaaa ... aaaaaa"

	std::thread thrd1(StartRakNetServer, raknetPort, broadcastInterval, msg);

	for (;;)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1000));
	}
}