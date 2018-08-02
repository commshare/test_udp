#include <thread>
#include <string.h>

bool StartRakNetServer(const char* bindIP, int port, int broadcastInterval, const char* broadcastMsg, int broadcastMsgLen);

int main(int argn, char* argv[])
{
	const int dataSzie = 400;				// ���ݰ���С
	int broadcastInterval = 100;			// �㲥���
	const int raknetPort = 5001;			// raknet server �˿ں�
	char* bindIP = "127.0.0.1";

	if (argn > 1)
	{
		broadcastInterval = atoi(argv[1]);
	}

	if (argn > 2)
	{
		bindIP = argv[2];
	}

	char msg[dataSzie] = { 0 };
	memset(msg, 97, dataSzie - 1);	// msg =  "aaaaa ... aaaaaa"

	std::thread thrd1(StartRakNetServer, bindIP, raknetPort, broadcastInterval, msg, dataSzie);

	for (;;)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1000));
	}
}